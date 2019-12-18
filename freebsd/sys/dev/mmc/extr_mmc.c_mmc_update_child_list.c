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
struct mmc_softc {int child_count; int /*<<< orphan*/ ** child_list; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** realloc (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmc_update_child_list(struct mmc_softc *sc)
{
	device_t child;
	int i, j;

	if (sc->child_count == 0) {
		free(sc->child_list, M_DEVBUF);
		return;
	}
	for (i = j = 0; i < sc->child_count; i++) {
		for (;;) {
			child = sc->child_list[j++];
			if (child != NULL)
				break;
		}
		if (i != j)
			sc->child_list[i] = child;
	}
	sc->child_list = realloc(sc->child_list, sizeof(device_t) *
	    sc->child_count, M_DEVBUF, M_WAITOK);
}