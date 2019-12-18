#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tp_col; } ;
struct TYPE_6__ {TYPE_1__ t_cursor; } ;
typedef  TYPE_2__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  teken_subr_cursor_up (TYPE_2__*,unsigned int) ; 

__attribute__((used)) static void
teken_subr_cursor_previous_line(teken_t *t, unsigned int ncols)
{

	t->t_cursor.tp_col = 0;
	teken_subr_cursor_up(t, ncols);
}