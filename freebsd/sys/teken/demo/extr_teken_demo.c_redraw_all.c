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
struct TYPE_3__ {scalar_t__ tp_row; scalar_t__ tp_col; } ;
typedef  TYPE_1__ teken_pos_t ;

/* Variables and functions */
 scalar_t__ NCOLS ; 
 scalar_t__ NROWS ; 
 int /*<<< orphan*/  printchar (TYPE_1__*) ; 
 int /*<<< orphan*/  redraw_border () ; 

__attribute__((used)) static void
redraw_all(void)
{
	teken_pos_t tp;

	for (tp.tp_row = 0; tp.tp_row < NROWS; tp.tp_row++)
		for (tp.tp_col = 0; tp.tp_col < NCOLS; tp.tp_col++)
			printchar(&tp);

	redraw_border();
}