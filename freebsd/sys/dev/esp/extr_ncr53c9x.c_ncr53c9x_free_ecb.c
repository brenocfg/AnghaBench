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
struct ncr53c9x_softc {int /*<<< orphan*/  free_list; } ;
struct ncr53c9x_ecb {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NCR_LOCK_ASSERT (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ncr53c9x_ecb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_links ; 

__attribute__((used)) static void
ncr53c9x_free_ecb(struct ncr53c9x_softc *sc, struct ncr53c9x_ecb *ecb)
{

	NCR_LOCK_ASSERT(sc, MA_OWNED);

	ecb->flags = 0;
	TAILQ_INSERT_TAIL(&sc->free_list, ecb, free_links);
}