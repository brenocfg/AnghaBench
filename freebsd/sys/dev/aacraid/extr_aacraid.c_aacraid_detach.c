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
struct aac_softc {int aifflags; int /*<<< orphan*/  aac_io_lock; int /*<<< orphan*/  eh; int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aifthread; int /*<<< orphan*/  aac_sim_tqh; int /*<<< orphan*/  aac_container_tqh; int /*<<< orphan*/  timeout_id; int /*<<< orphan*/  aac_daemontime; } ;
struct aac_sim {int /*<<< orphan*/  sim_dev; } ;
struct aac_container {int /*<<< orphan*/  sim_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AAC_AIFFLAGS_EXIT ; 
 int AAC_AIFFLAGS_RUNNING ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  M_AACRAIDBUF ; 
 int PCATCH ; 
 int PUSER ; 
 struct aac_sim* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct aac_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aac_daemon ; 
 int /*<<< orphan*/  aacraid_free (struct aac_softc*) ; 
 int aacraid_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  co_link ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct aac_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  shutdown_final ; 
 int /*<<< orphan*/  sim_link ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  untimeout (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

int
aacraid_detach(device_t dev)
{
	struct aac_softc *sc;
	struct aac_container *co;
	struct aac_sim	*sim;
	int error;

	sc = device_get_softc(dev);
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

#if __FreeBSD_version >= 800000
	callout_drain(&sc->aac_daemontime);
#else
	untimeout(aac_daemon, (void *)sc, sc->timeout_id);
#endif
	/* Remove the child containers */
	while ((co = TAILQ_FIRST(&sc->aac_container_tqh)) != NULL) {
		TAILQ_REMOVE(&sc->aac_container_tqh, co, co_link);
		free(co, M_AACRAIDBUF);
	}

	/* Remove the CAM SIMs */
	while ((sim = TAILQ_FIRST(&sc->aac_sim_tqh)) != NULL) {
		TAILQ_REMOVE(&sc->aac_sim_tqh, sim, sim_link);
		error = device_delete_child(dev, sim->sim_dev);
		if (error)
			return (error);
		free(sim, M_AACRAIDBUF);
	}

	if (sc->aifflags & AAC_AIFFLAGS_RUNNING) {
		sc->aifflags |= AAC_AIFFLAGS_EXIT;
		wakeup(sc->aifthread);
		tsleep(sc->aac_dev, PUSER | PCATCH, "aac_dch", 30 * hz);
	}

	if (sc->aifflags & AAC_AIFFLAGS_RUNNING)
		panic("Cannot shutdown AIF thread");

	if ((error = aacraid_shutdown(dev)))
		return(error);

	EVENTHANDLER_DEREGISTER(shutdown_final, sc->eh);

	aacraid_free(sc);

	mtx_destroy(&sc->aac_io_lock);

	return(0);
}