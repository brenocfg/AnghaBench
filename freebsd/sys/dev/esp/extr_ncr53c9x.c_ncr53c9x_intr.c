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
struct ncr53c9x_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCRDMA_ISINTR (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  NCR_LOCK (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  NCR_UNLOCK (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  ncr53c9x_intr1 (struct ncr53c9x_softc*) ; 

void
ncr53c9x_intr(void *arg)
{
	struct ncr53c9x_softc *sc = arg;

	if (!NCRDMA_ISINTR(sc))
		return;

	NCR_LOCK(sc);

	ncr53c9x_intr1(sc);

	NCR_UNLOCK(sc);
}