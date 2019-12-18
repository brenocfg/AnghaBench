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
struct cpswp_softc {int /*<<< orphan*/  swsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CPSW_PORT_LOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  CPSW_PORT_UNLOCK (struct cpswp_softc*) ; 
 int /*<<< orphan*/  cpswp_init_locked (void*) ; 

__attribute__((used)) static void
cpswp_init(void *arg)
{
	struct cpswp_softc *sc = arg;

	CPSW_DEBUGF(sc->swsc, (""));
	CPSW_PORT_LOCK(sc);
	cpswp_init_locked(arg);
	CPSW_PORT_UNLOCK(sc);
}