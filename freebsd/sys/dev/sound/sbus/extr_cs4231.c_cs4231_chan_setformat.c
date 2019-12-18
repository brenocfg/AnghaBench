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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct cs4231_softc {int dummy; } ;
struct cs4231_channel {int format; scalar_t__ dir; struct cs4231_softc* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  AFMT_A_LAW 133 
 int AFMT_CHANNEL (int) ; 
 int AFMT_ENCODING (int) ; 
#define  AFMT_IMA_ADPCM 132 
#define  AFMT_MU_LAW 131 
#define  AFMT_S16_BE 130 
#define  AFMT_S16_LE 129 
#define  AFMT_U8 128 
 int /*<<< orphan*/  CS4231_LOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS4231_UNLOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS_AFMT_A_LAW ; 
 int /*<<< orphan*/  CS_AFMT_IMA_ADPCM ; 
 int /*<<< orphan*/  CS_AFMT_MU_LAW ; 
 int /*<<< orphan*/  CS_AFMT_S16_BE ; 
 int /*<<< orphan*/  CS_AFMT_S16_LE ; 
 int /*<<< orphan*/  CS_AFMT_STEREO ; 
 int /*<<< orphan*/  CS_AFMT_U8 ; 
 int /*<<< orphan*/  CS_CLOCK_DATA_FORMAT ; 
 int /*<<< orphan*/  CS_CLOCK_DATA_FORMAT_MASK ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  cs4231_chan_fs (struct cs4231_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4231_read (struct cs4231_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cs4231_chan_setformat(kobj_t obj, void *data, u_int32_t format)
{
	struct cs4231_softc *sc;
	struct cs4231_channel *ch;
	u_int32_t encoding;
	u_int8_t fs, v;

	ch = data;
	sc = ch->parent;

	CS4231_LOCK(sc);
	if (ch->format == format) {
		CS4231_UNLOCK(sc);
		return (0);
	}

	encoding = AFMT_ENCODING(format);
	fs = 0;
	switch (encoding) {
	case AFMT_U8:
		fs = CS_AFMT_U8;
		break;
	case AFMT_MU_LAW:
		fs = CS_AFMT_MU_LAW;
		break;
	case AFMT_S16_LE:
		fs = CS_AFMT_S16_LE;
		break;
	case AFMT_A_LAW:
		fs = CS_AFMT_A_LAW;
		break;
	case AFMT_IMA_ADPCM:
		fs = CS_AFMT_IMA_ADPCM;
		break;
	case AFMT_S16_BE:
		fs = CS_AFMT_S16_BE;
		break;
	default:
		fs = CS_AFMT_U8;
		format = AFMT_U8;
		break;
	}

	if (AFMT_CHANNEL(format) > 1)
		fs |= CS_AFMT_STEREO;
	
	DPRINTF(("FORMAT: %s : 0x%x\n", ch->dir == PCMDIR_PLAY ? "playback" :
	    "capture", format));
	v = cs4231_read(sc, CS_CLOCK_DATA_FORMAT);
	v &= CS_CLOCK_DATA_FORMAT_MASK;
	fs |= v;
	cs4231_chan_fs(sc, ch->dir, fs);
	ch->format = format;
	CS4231_UNLOCK(sc);

	return (0);
}