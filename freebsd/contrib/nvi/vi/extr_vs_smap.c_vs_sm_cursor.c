#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ lno; scalar_t__ cno; } ;
struct TYPE_10__ {scalar_t__ lno; scalar_t__ c_eboff; } ;
typedef  TYPE_1__ SMAP ;
typedef  TYPE_2__ SCR ;

/* Variables and functions */
 TYPE_1__* HMAP ; 
 int /*<<< orphan*/  SMAP_CACHE (TYPE_1__*) ; 
 TYPE_1__* TMAP ; 
 scalar_t__ vs_line (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
vs_sm_cursor(SCR *sp, SMAP **smpp)
{
	SMAP *p;

	/* See if the cursor is not in the map. */
	if (sp->lno < HMAP->lno || sp->lno > TMAP->lno)
		return (1);

	/* Find the first occurence of the line. */
	for (p = HMAP; p->lno != sp->lno; ++p);

	/* Fill in the map information until we find the right line. */
	for (; p <= TMAP; ++p) {
		/* Short lines are common and easy to detect. */
		if (p != TMAP && (p + 1)->lno != p->lno) {
			*smpp = p;
			return (0);
		}
		if (!SMAP_CACHE(p) && vs_line(sp, p, NULL, NULL))
			return (1);
		if (p->c_eboff >= sp->cno) {
			*smpp = p;
			return (0);
		}
	}

	/* It was past the end of the map after all. */
	return (1);
}