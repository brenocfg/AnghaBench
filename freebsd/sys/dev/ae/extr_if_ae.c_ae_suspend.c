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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ae_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AE_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ae_pm_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ae_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ae_suspend(device_t dev)
{
	ae_softc_t *sc;

	sc = device_get_softc(dev);

	AE_LOCK(sc);
	ae_stop(sc);
	ae_pm_init(sc);
	AE_UNLOCK(sc);

	return (0);
}