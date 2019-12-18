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
struct ste_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STE_LOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  STE_UNLOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_init_locked (struct ste_softc*) ; 

__attribute__((used)) static void
ste_init(void *xsc)
{
	struct ste_softc *sc;

	sc = xsc;
	STE_LOCK(sc);
	ste_init_locked(sc);
	STE_UNLOCK(sc);
}