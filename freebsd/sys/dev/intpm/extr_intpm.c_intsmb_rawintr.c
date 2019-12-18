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
struct intsmb_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTSMB_LOCK (struct intsmb_softc*) ; 
 int /*<<< orphan*/  INTSMB_UNLOCK (struct intsmb_softc*) ; 
 int /*<<< orphan*/  intsmb_intr (struct intsmb_softc*) ; 
 int /*<<< orphan*/  intsmb_slvintr (struct intsmb_softc*) ; 

__attribute__((used)) static void
intsmb_rawintr(void *arg)
{
	struct intsmb_softc *sc = arg;

	INTSMB_LOCK(sc);
	intsmb_intr(sc);
	intsmb_slvintr(sc);
	INTSMB_UNLOCK(sc);
}