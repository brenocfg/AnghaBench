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
struct mwl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWL_LOCK (struct mwl_softc*) ; 
 int /*<<< orphan*/  MWL_UNLOCK (struct mwl_softc*) ; 
 int /*<<< orphan*/  mwl_stop (struct mwl_softc*) ; 

void
mwl_shutdown(void *arg)
{
	struct mwl_softc *sc = arg;

	MWL_LOCK(sc);
	mwl_stop(sc);
	MWL_UNLOCK(sc);
}