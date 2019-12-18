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
typedef  int /*<<< orphan*/  ae_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AE_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ae_init_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ae_init(void *arg)
{
	ae_softc_t *sc;

	sc = (ae_softc_t *)arg;
	AE_LOCK(sc);
	ae_init_locked(sc);
	AE_UNLOCK(sc);
}