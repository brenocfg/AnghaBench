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
struct age_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_LOCK (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_UNLOCK (struct age_softc*) ; 
 int /*<<< orphan*/  age_init_locked (struct age_softc*) ; 

__attribute__((used)) static void
age_init(void *xsc)
{
	struct age_softc *sc;

	sc = (struct age_softc *)xsc;
	AGE_LOCK(sc);
	age_init_locked(sc);
	AGE_UNLOCK(sc);
}