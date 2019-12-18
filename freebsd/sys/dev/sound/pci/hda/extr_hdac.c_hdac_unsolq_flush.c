#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct hdac_softc {scalar_t__ unsolq_st; size_t* unsolq; TYPE_1__* codecs; int /*<<< orphan*/  unsolq_rp; int /*<<< orphan*/  unsolq_wp; } ;
typedef  size_t nid_t ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 scalar_t__ HDAC_UNSOLQ_BUSY ; 
 int /*<<< orphan*/  HDAC_UNSOLQ_MAX ; 
 scalar_t__ HDAC_UNSOLQ_READY ; 
 int /*<<< orphan*/  HDAC_UNSOL_INTR (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
hdac_unsolq_flush(struct hdac_softc *sc)
{
	device_t child;
	nid_t cad;
	uint32_t resp;
	int ret = 0;

	if (sc->unsolq_st == HDAC_UNSOLQ_READY) {
		sc->unsolq_st = HDAC_UNSOLQ_BUSY;
		while (sc->unsolq_rp != sc->unsolq_wp) {
			resp = sc->unsolq[sc->unsolq_rp++];
			sc->unsolq_rp %= HDAC_UNSOLQ_MAX;
			cad = sc->unsolq[sc->unsolq_rp++];
			sc->unsolq_rp %= HDAC_UNSOLQ_MAX;
			if ((child = sc->codecs[cad].dev) != NULL)
				HDAC_UNSOL_INTR(child, resp);
			ret++;
		}
		sc->unsolq_st = HDAC_UNSOLQ_READY;
	}

	return (ret);
}