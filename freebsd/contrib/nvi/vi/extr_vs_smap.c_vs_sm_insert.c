#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ recno_t ;
struct TYPE_17__ {TYPE_1__* gp; } ;
struct TYPE_16__ {size_t coff; scalar_t__ lno; size_t soff; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* scr_move ) (TYPE_3__*,int,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ SMAP ;
typedef  TYPE_3__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  HANDLE_WEIRDNESS (size_t) ; 
 TYPE_2__* HMAP ; 
 int /*<<< orphan*/  SMAP_FLUSH (TYPE_2__*) ; 
 TYPE_2__* TMAP ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vs_insertln (TYPE_3__*,size_t) ; 
 scalar_t__ vs_line (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t vs_screens (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vs_sm_insert(SCR *sp, recno_t lno)
{
	SMAP *p, *t;
	size_t cnt_orig, cnt, coff;

	/* Save the offset. */
	coff = HMAP->coff;

	/*
	 * Find the line in the map, find out how many screen lines
	 * needed to display the line.
	 */
	for (p = HMAP; p->lno != lno; ++p);

	cnt_orig = vs_screens(sp, lno, NULL);
	HANDLE_WEIRDNESS(cnt_orig);

	/*
	 * The lines left in the screen override the number of screen
	 * lines in the inserted line.
	 */
	cnt = (TMAP - p) + 1;
	if (cnt_orig > cnt)
		cnt_orig = cnt;

	/* Push down that many lines. */
	(void)sp->gp->scr_move(sp, p - HMAP, 0);
	if (vs_insertln(sp, cnt_orig))
		return (1);

	/* Shift the screen map down. */
	memmove(p + cnt_orig, p, (((TMAP - p) - cnt_orig) + 1) * sizeof(SMAP));

	/* Increment the line numbers for the rest of the map. */
	for (t = p + cnt_orig; t <= TMAP; ++t)
		++t->lno;

	/* Fill in the SMAP for the new lines, and display. */
	for (cnt = 1, t = p; cnt <= cnt_orig; ++t, ++cnt) {
		t->lno = lno;
		t->coff = coff;
		t->soff = cnt;
		SMAP_FLUSH(t);
		if (vs_line(sp, t, NULL, NULL))
			return (1);
	}
	return (0);
}