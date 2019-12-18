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
 int /*<<< orphan*/  line_update (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  summary_format (char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap_buffer ; 
 int /*<<< orphan*/ * swap_names ; 
 int /*<<< orphan*/  x_swap ; 
 int /*<<< orphan*/  y_swap ; 

void
u_swap(int *stats)
{
    static char *new = NULL;

    new = setup_buffer(new, 0);

    if (swap_names == NULL)
	    return;

    /* format the new line */
    summary_format(new, stats, swap_names);
    line_update(swap_buffer, new, x_swap, y_swap);
}