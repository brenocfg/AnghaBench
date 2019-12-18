#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  EL_GETTC ; 
 int /*<<< orphan*/  e ; 
 int /*<<< orphan*/  el_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

void
rl_get_screen_size(int *rows, int *cols)
{
	if (rows)
		el_get(e, EL_GETTC, "li", rows);
	if (cols)
		el_get(e, EL_GETTC, "co", cols);
}