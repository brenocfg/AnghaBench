#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct g_bde_work {int /*<<< orphan*/  so; TYPE_1__* softc; } ;
struct g_bde_sector {int malloc; int size; int ref; int /*<<< orphan*/  state; int /*<<< orphan*/  offset; struct g_bde_work* owner; TYPE_1__* softc; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int /*<<< orphan*/  nsect; } ;

/* Variables and functions */
 int /*<<< orphan*/  JUNK ; 
 int /*<<< orphan*/  M_GBDE ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct g_bde_sector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_bde_nsect ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct g_bde_sector *
g_bde_new_sector(struct g_bde_work *wp, u_int len)
{
	struct g_bde_sector *sp;

	sp = malloc(sizeof *sp, M_GBDE, M_NOWAIT | M_ZERO);
	if (sp == NULL)
		return (sp);
	if (len > 0) {
		sp->data = malloc(len, M_GBDE, M_NOWAIT | M_ZERO);
		if (sp->data == NULL) {
			free(sp, M_GBDE);
			return (NULL);
		}
		sp->malloc = 1;
	}
	g_bde_nsect++;
	wp->softc->nsect++;
	sp->size = len;
	sp->softc = wp->softc;
	sp->ref = 1;
	sp->owner = wp;
	sp->offset = wp->so;
	sp->state = JUNK;
	return (sp);
}