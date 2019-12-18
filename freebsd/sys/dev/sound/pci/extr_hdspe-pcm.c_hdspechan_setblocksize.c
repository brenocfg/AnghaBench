#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct sc_pcminfo {int /*<<< orphan*/  dev; struct sc_info* sc; } ;
struct sc_info {int period; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrl_register; } ;
struct sc_chinfo {int /*<<< orphan*/  buffer; struct sc_pcminfo* parent; } ;
struct hdspe_latency {int period; int /*<<< orphan*/  n; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int HDSPE_CHANBUF_SIZE ; 
 int /*<<< orphan*/  HDSPE_CONTROL_REG ; 
 int HDSPE_LAT_BYTES_MAX ; 
 int HDSPE_LAT_BYTES_MIN ; 
 int /*<<< orphan*/  HDSPE_LAT_MASK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hdspe_encode_latency (int /*<<< orphan*/ ) ; 
 int hdspe_running (struct sc_info*) ; 
 int /*<<< orphan*/  hdspe_write_4 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hdspe_latency* latency_map ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int sndbuf_getblksz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_resize (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static uint32_t
hdspechan_setblocksize(kobj_t obj, void *data, uint32_t blocksize)
{
	struct hdspe_latency *hl;
	struct sc_pcminfo *scp;
	struct sc_chinfo *ch;
	struct sc_info *sc;
	int threshold;
	int i;

	ch = data;
	scp = ch->parent;
	sc = scp->sc;
	hl = NULL;

#if 0
	device_printf(scp->dev, "hdspechan_setblocksize(%d)\n", blocksize);
#endif

	if (hdspe_running(sc) == 1)
		goto end;

	if (blocksize > HDSPE_LAT_BYTES_MAX)
		blocksize = HDSPE_LAT_BYTES_MAX;
	else if (blocksize < HDSPE_LAT_BYTES_MIN)
		blocksize = HDSPE_LAT_BYTES_MIN;

	blocksize /= 4 /* samples */;

	/* First look for equal latency. */
	for (i = 0; latency_map[i].period != 0; i++) {
		if (latency_map[i].period == blocksize) {
			hl = &latency_map[i];
		}
	}

	/* If no match, just find nearest. */
	if (hl == NULL) {
		for (i = 0; latency_map[i].period != 0; i++) {
			hl = &latency_map[i];
			threshold = hl->period + ((latency_map[i + 1].period != 0) ?
			    ((latency_map[i + 1].period - hl->period) >> 1) : 0);
			if (blocksize < threshold)
				break;
		}
	}

	snd_mtxlock(sc->lock);
	sc->ctrl_register &= ~HDSPE_LAT_MASK;
	sc->ctrl_register |= hdspe_encode_latency(hl->n);
	hdspe_write_4(sc, HDSPE_CONTROL_REG, sc->ctrl_register);
	sc->period = hl->period;
	snd_mtxunlock(sc->lock);

#if 0
	device_printf(scp->dev, "New period=%d\n", sc->period);
#endif

	sndbuf_resize(ch->buffer, (HDSPE_CHANBUF_SIZE * 2) / (sc->period * 4),
	    (sc->period * 4));
end:

	return (sndbuf_getblksz(ch->buffer));
}