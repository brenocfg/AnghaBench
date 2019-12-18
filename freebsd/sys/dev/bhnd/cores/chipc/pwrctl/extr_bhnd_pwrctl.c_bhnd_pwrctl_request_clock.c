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
struct bhnd_pwrctl_softc {int /*<<< orphan*/  clkres_list; } ;
struct bhnd_pwrctl_clkres {scalar_t__ clock; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bhnd_clock ;

/* Variables and functions */
 scalar_t__ BHND_CLOCK_DYN ; 
 int /*<<< orphan*/  BHND_PWRCTL_WAR_RUN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PWRCTL_LOCK (struct bhnd_pwrctl_softc*) ; 
 int /*<<< orphan*/  PWRCTL_UNLOCK (struct bhnd_pwrctl_softc*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bhnd_pwrctl_clkres*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct bhnd_pwrctl_clkres*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_pwrctl_clkres ; 
 struct bhnd_pwrctl_clkres* bhnd_pwrctl_find_res (struct bhnd_pwrctl_softc*,int /*<<< orphan*/ ) ; 
 int bhnd_pwrctl_updateclk (struct bhnd_pwrctl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cr_link ; 
 struct bhnd_pwrctl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (struct bhnd_pwrctl_clkres*,int /*<<< orphan*/ ) ; 
 struct bhnd_pwrctl_clkres* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_pwrctl_request_clock(device_t dev, device_t child, bhnd_clock clock)
{
	struct bhnd_pwrctl_softc	*sc;
	struct bhnd_pwrctl_clkres	*clkres;
	int				 error;

	sc = device_get_softc(dev);
	error = 0;

	PWRCTL_LOCK(sc);

	clkres = bhnd_pwrctl_find_res(sc, child);

	/* BHND_CLOCK_DYN discards the clock reservation entirely */
	if (clock == BHND_CLOCK_DYN) {
		/* nothing to clean up? */
		if (clkres == NULL) {
			PWRCTL_UNLOCK(sc);
			return (0);
		}

		/* drop reservation and apply clock transition */
		STAILQ_REMOVE(&sc->clkres_list, clkres,
		    bhnd_pwrctl_clkres, cr_link);

		if ((error = bhnd_pwrctl_updateclk(sc, BHND_PWRCTL_WAR_RUN))) {
			device_printf(dev, "clock transition failed: %d\n",
			    error);

			/* restore reservation */
			STAILQ_INSERT_TAIL(&sc->clkres_list, clkres, cr_link);

			PWRCTL_UNLOCK(sc);
			return (error);
		}

		/* deallocate orphaned reservation */
		free(clkres, M_DEVBUF);

		PWRCTL_UNLOCK(sc);
		return (0);
	}

	/* create (or update) reservation */
	if (clkres == NULL) {
		clkres = malloc(sizeof(struct bhnd_pwrctl_clkres), M_DEVBUF,
		    M_NOWAIT);
		if (clkres == NULL)
			return (ENOMEM);

		clkres->owner = child;
		clkres->clock = clock;

		STAILQ_INSERT_TAIL(&sc->clkres_list, clkres, cr_link);
	} else {
		KASSERT(clkres->owner == child, ("invalid owner"));
		clkres->clock = clock;
	}

	/* apply clock transition */
	error = bhnd_pwrctl_updateclk(sc, BHND_PWRCTL_WAR_RUN);
	if (error) {
		STAILQ_REMOVE(&sc->clkres_list, clkres, bhnd_pwrctl_clkres,
		    cr_link);
		free(clkres, M_DEVBUF);
	}

	PWRCTL_UNLOCK(sc);
	return (error);
}