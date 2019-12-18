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
struct vte_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTE_LOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  VTE_UNLOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_init_locked (struct vte_softc*) ; 

__attribute__((used)) static void
vte_init(void *xsc)
{
	struct vte_softc *sc;

	sc = (struct vte_softc *)xsc;
	VTE_LOCK(sc);
	vte_init_locked(sc);
	VTE_UNLOCK(sc);
}