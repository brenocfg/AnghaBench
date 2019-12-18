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
struct gem_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_LOCK (struct gem_softc*) ; 
 int /*<<< orphan*/  GEM_UNLOCK (struct gem_softc*) ; 
 int /*<<< orphan*/  gem_init_locked (struct gem_softc*) ; 

__attribute__((used)) static void
gem_init(void *xsc)
{
	struct gem_softc *sc = xsc;

	GEM_LOCK(sc);
	gem_init_locked(sc);
	GEM_UNLOCK(sc);
}