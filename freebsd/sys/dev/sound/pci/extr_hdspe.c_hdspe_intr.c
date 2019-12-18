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
struct sc_pcminfo {int /*<<< orphan*/  (* ih ) (struct sc_pcminfo*) ;} ;
struct sc_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int HDSPE_AUDIO_IRQ_PENDING ; 
 int /*<<< orphan*/  HDSPE_INTERRUPT_ACK ; 
 int /*<<< orphan*/  HDSPE_STATUS_REG ; 
 int /*<<< orphan*/  M_TEMP ; 
 int device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 struct sc_pcminfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hdspe_read_1 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdspe_write_1 (struct sc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxunlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sc_pcminfo*) ; 

__attribute__((used)) static void
hdspe_intr(void *p)
{
	struct sc_pcminfo *scp;
	struct sc_info *sc;
	device_t *devlist;
	int devcount;
	int status;
	int err;
	int i;

	sc = (struct sc_info *)p;

	snd_mtxlock(sc->lock);

	status = hdspe_read_1(sc, HDSPE_STATUS_REG);
	if (status & HDSPE_AUDIO_IRQ_PENDING) {
		if ((err = device_get_children(sc->dev, &devlist, &devcount)) != 0)
			return;

		for (i = 0; i < devcount; i++) {
			scp = device_get_ivars(devlist[i]);
			if (scp->ih != NULL)
				scp->ih(scp);
		}

		hdspe_write_1(sc, HDSPE_INTERRUPT_ACK, 0);
		free(devlist, M_TEMP);
	}

	snd_mtxunlock(sc->lock);
}