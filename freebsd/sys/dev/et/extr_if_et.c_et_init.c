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
struct et_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_LOCK (struct et_softc*) ; 
 int /*<<< orphan*/  ET_UNLOCK (struct et_softc*) ; 
 int /*<<< orphan*/  et_init_locked (struct et_softc*) ; 

__attribute__((used)) static void
et_init(void *xsc)
{
	struct et_softc *sc = xsc;

	ET_LOCK(sc);
	et_init_locked(sc);
	ET_UNLOCK(sc);
}