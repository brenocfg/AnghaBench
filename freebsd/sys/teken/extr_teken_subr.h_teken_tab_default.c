#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  t_tabstops; } ;
typedef  TYPE_1__ teken_t ;

/* Variables and functions */
 int T_NUMCOL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  teken_tab_set (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void
teken_tab_default(teken_t *t)
{
	unsigned int i;

	memset(t->t_tabstops, 0, T_NUMCOL / 8);

	for (i = 8; i < T_NUMCOL; i += 8)
		teken_tab_set(t, i);
}