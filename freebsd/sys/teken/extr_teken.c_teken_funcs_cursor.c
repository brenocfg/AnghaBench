#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_6__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_8__ {TYPE_5__ t_cursor; int /*<<< orphan*/  t_softc; TYPE_2__* t_funcs; TYPE_1__ t_winsize; } ;
typedef  TYPE_3__ teken_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* tf_cursor ) (int /*<<< orphan*/ ,TYPE_5__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  teken_assert (int) ; 

__attribute__((used)) static inline void
teken_funcs_cursor(const teken_t *t)
{

	teken_assert(t->t_cursor.tp_row < t->t_winsize.tp_row);
	teken_assert(t->t_cursor.tp_col < t->t_winsize.tp_col);

	teken_assert(t->t_funcs->tf_cursor != NULL);
	t->t_funcs->tf_cursor(t->t_softc, &t->t_cursor);
}