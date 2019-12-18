#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t soff; scalar_t__ lno; int /*<<< orphan*/  coff; } ;
typedef  TYPE_1__ SMAP ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 scalar_t__ O_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_LEFTRIGHT ; 
 int /*<<< orphan*/  SMAP_FLUSH (TYPE_1__*) ; 
 size_t vs_screens (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

int
vs_sm_next(SCR *sp, SMAP *p, SMAP *t)
{
	size_t lcnt;

	SMAP_FLUSH(t);
	if (O_ISSET(sp, O_LEFTRIGHT)) {
		t->lno = p->lno + 1;
		t->coff = p->coff;
	} else {
		lcnt = vs_screens(sp, p->lno, NULL);
		if (lcnt == p->soff) {
			t->lno = p->lno + 1;
			t->soff = 1;
		} else {
			t->lno = p->lno;
			t->soff = p->soff + 1;
		}
	}
	return (0);
}