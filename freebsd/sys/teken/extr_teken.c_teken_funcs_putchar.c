#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_softc; TYPE_2__* t_funcs; TYPE_1__ t_winsize; } ;
typedef  TYPE_3__ teken_t ;
struct TYPE_11__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
typedef  TYPE_4__ teken_pos_t ;
typedef  int /*<<< orphan*/  teken_char_t ;
typedef  int /*<<< orphan*/  teken_attr_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* tf_putchar ) (int /*<<< orphan*/ ,TYPE_4__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  teken_assert (int) ; 

__attribute__((used)) static inline void
teken_funcs_putchar(const teken_t *t, const teken_pos_t *p, teken_char_t c,
    const teken_attr_t *a)
{

	teken_assert(p->tp_row < t->t_winsize.tp_row);
	teken_assert(p->tp_col < t->t_winsize.tp_col);

	teken_assert(t->t_funcs->tf_putchar != NULL);
	t->t_funcs->tf_putchar(t->t_softc, p, c, a);
}