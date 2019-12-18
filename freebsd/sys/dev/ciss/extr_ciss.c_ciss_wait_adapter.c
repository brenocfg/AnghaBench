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
struct ciss_softc {TYPE_1__* ciss_cfg; } ;
struct TYPE_2__ {int active_method; } ;

/* Variables and functions */
 int CISS_TRANSPORT_METHOD_READY ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
ciss_wait_adapter(struct ciss_softc *sc)
{
    int		i;

    debug_called(1);

    /*
     * Wait for the adapter to come ready.
     */
    if (!(sc->ciss_cfg->active_method & CISS_TRANSPORT_METHOD_READY)) {
	ciss_printf(sc, "waiting for adapter to come ready...\n");
	for (i = 0; !(sc->ciss_cfg->active_method & CISS_TRANSPORT_METHOD_READY); i++) {
	    DELAY(1000000);	/* one second */
	    if (i > 30) {
		ciss_printf(sc, "timed out waiting for adapter to come ready\n");
		return(EIO);
	    }
	}
    }
    return(0);
}