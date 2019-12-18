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
struct g_bde_softc {int /*<<< orphan*/  nsect; } ;
struct g_bde_sector {struct g_bde_sector* data; scalar_t__ malloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_GBDE ; 
 int /*<<< orphan*/  free (struct g_bde_sector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_bde_nsect ; 

__attribute__((used)) static void
g_bde_delete_sector(struct g_bde_softc *sc, struct g_bde_sector *sp)
{

	g_bde_nsect--;
	sc->nsect--;
	if (sp->malloc)
		free(sp->data, M_GBDE);
	free(sp, M_GBDE);
}