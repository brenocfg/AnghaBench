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
struct bhnd_pwrctl_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PWRCTL_WAR_UP ; 
 int /*<<< orphan*/  PWRCTL_LOCK (struct bhnd_pwrctl_softc*) ; 
 int /*<<< orphan*/  PWRCTL_UNLOCK (struct bhnd_pwrctl_softc*) ; 
 int bhnd_pwrctl_init (struct bhnd_pwrctl_softc*) ; 
 int bhnd_pwrctl_updateclk (struct bhnd_pwrctl_softc*,int /*<<< orphan*/ ) ; 
 struct bhnd_pwrctl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bhnd_pwrctl_resume(device_t dev)
{
	struct bhnd_pwrctl_softc	*sc;
	int				 error;

	sc = device_get_softc(dev);

	PWRCTL_LOCK(sc);

	/* Re-initialize power control registers */
	if ((error = bhnd_pwrctl_init(sc))) {
		device_printf(sc->dev, "PWRCTL init failed: %d\n", error);
		goto cleanup;
	}

	/* Restore clock state */
	if ((error = bhnd_pwrctl_updateclk(sc, BHND_PWRCTL_WAR_UP))) {
		device_printf(sc->dev, "clock state restore failed: %d\n",
		    error);
		goto cleanup;
	}

cleanup:
	PWRCTL_UNLOCK(sc);
	return (error);
}