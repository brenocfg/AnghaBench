#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_14__ {int /*<<< orphan*/  t_softc; TYPE_4__* t_funcs; TYPE_3__ t_winsize; } ;
typedef  TYPE_5__ teken_t ;
struct TYPE_11__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_10__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_15__ {TYPE_2__ tr_end; TYPE_1__ tr_begin; } ;
typedef  TYPE_6__ teken_rect_t ;
typedef  int /*<<< orphan*/  teken_char_t ;
typedef  int /*<<< orphan*/  teken_attr_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* tf_fill ) (int /*<<< orphan*/ ,TYPE_6__ const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_6__ const*,int /*<<< orphan*/  const,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  teken_assert (int) ; 

__attribute__((used)) static inline void
teken_funcs_fill(const teken_t *t, const teken_rect_t *r,
    const teken_char_t c, const teken_attr_t *a)
{

	teken_assert(r->tr_end.tp_row > r->tr_begin.tp_row);
	teken_assert(r->tr_end.tp_row <= t->t_winsize.tp_row);
	teken_assert(r->tr_end.tp_col > r->tr_begin.tp_col);
	teken_assert(r->tr_end.tp_col <= t->t_winsize.tp_col);

	teken_assert(t->t_funcs->tf_fill != NULL);
	t->t_funcs->tf_fill(t->t_softc, r, c, a);
}