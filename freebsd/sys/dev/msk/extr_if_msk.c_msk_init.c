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
struct msk_if_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSK_IF_LOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_IF_UNLOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_init_locked (struct msk_if_softc*) ; 

__attribute__((used)) static void
msk_init(void *xsc)
{
	struct msk_if_softc *sc_if = xsc;

	MSK_IF_LOCK(sc_if);
	msk_init_locked(sc_if);
	MSK_IF_UNLOCK(sc_if);
}