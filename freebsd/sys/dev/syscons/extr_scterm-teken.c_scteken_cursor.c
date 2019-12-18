#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tp_row; int /*<<< orphan*/  tp_col; } ;
typedef  TYPE_1__ teken_pos_t ;
typedef  int /*<<< orphan*/  scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  sc_move_cursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
scteken_cursor(void *arg, const teken_pos_t *p)
{
	scr_stat *scp = arg;

	sc_move_cursor(scp, p->tp_col, p->tp_row);
}