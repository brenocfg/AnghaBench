#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  size_t u_char ;
struct TYPE_10__ {int tp_row; int tp_col; } ;
typedef  TYPE_2__ teken_pos_t ;
typedef  size_t teken_char_t ;
struct TYPE_11__ {int ta_format; } ;
typedef  TYPE_3__ teken_attr_t ;
struct TYPE_12__ {int xsize; int ysize; int /*<<< orphan*/  vtb; TYPE_1__* sc; } ;
typedef  TYPE_4__ scr_stat ;
struct TYPE_9__ {size_t* scr_map; } ;

/* Variables and functions */
 int TF_CJK_RIGHT ; 
 int imin (int,int) ; 
 int /*<<< orphan*/  mark_for_update (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sc_vtb_pointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sc_vtb_putchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  scteken_get_cp437 (size_t*,int*) ; 
 int scteken_te_to_sc_attr (TYPE_3__ const*) ; 

__attribute__((used)) static void
scteken_putchar(void *arg, const teken_pos_t *tp, teken_char_t c,
    const teken_attr_t *a)
{
	scr_stat *scp = arg;
	u_char *map;
	u_char ch;
	vm_offset_t p;
	int cursor, attr;

	/*
	 * No support for printing right hand sides for CJK fullwidth
	 * characters. Simply print a space and assume that the left
	 * hand side describes the entire character.
	 */
	attr = scteken_te_to_sc_attr(a) << 8;
	if (a->ta_format & TF_CJK_RIGHT)
		c = ' ';
#ifdef TEKEN_UTF8
	scteken_get_cp437(&c, &attr);
#endif /* TEKEN_UTF8 */
	ch = c;

	map = scp->sc->scr_map;

	cursor = tp->tp_row * scp->xsize + tp->tp_col;
	p = sc_vtb_pointer(&scp->vtb, cursor);
	sc_vtb_putchar(&scp->vtb, p, map[ch], attr);

	mark_for_update(scp, cursor);
	/*
	 * XXX: Why do we need this? Only marking `cursor' should be
	 * enough. Without this line, we get artifacts.
	 */
	mark_for_update(scp, imin(cursor + 1, scp->xsize * scp->ysize - 1));
}