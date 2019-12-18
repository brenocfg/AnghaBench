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
struct cyapa_softc {int dummy; } ;
struct cyapa_fifo {scalar_t__ windex; scalar_t__ rindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_LOCK_ASSERT (struct cyapa_softc*) ; 

__attribute__((used)) static void
fifo_reset(struct cyapa_softc *sc, struct cyapa_fifo *fifo)
{

	CYAPA_LOCK_ASSERT(sc);

	fifo->rindex = 0;
	fifo->windex = 0;
}