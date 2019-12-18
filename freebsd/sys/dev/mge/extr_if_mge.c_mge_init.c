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
struct mge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGE_GLOBAL_LOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_GLOBAL_UNLOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  mge_init_locked (void*) ; 

__attribute__((used)) static void
mge_init(void *arg)
{
	struct mge_softc *sc;

	sc = arg;
	MGE_GLOBAL_LOCK(sc);

	mge_init_locked(arg);

	MGE_GLOBAL_UNLOCK(sc);
}