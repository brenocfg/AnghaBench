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
struct TYPE_5__ {int /*<<< orphan*/  tp_col; } ;
struct TYPE_6__ {TYPE_1__ t_cursor; } ;
typedef  TYPE_2__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  teken_tab_set (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
teken_subr_horizontal_tab_set(teken_t *t)
{

	teken_tab_set(t, t->t_cursor.tp_col);
}