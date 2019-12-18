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
struct vtballoon_softc {int /*<<< orphan*/  vtballoon_current_npages; int /*<<< orphan*/  vtballoon_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtballoon_deflate (struct vtballoon_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtballoon_pop(struct vtballoon_softc *sc)
{

	while (!TAILQ_EMPTY(&sc->vtballoon_pages))
		vtballoon_deflate(sc, sc->vtballoon_current_npages);
}