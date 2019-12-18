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
 int /*<<< orphan*/  memory_buffer ; 
 int /*<<< orphan*/  memory_names ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  summary_format (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x_mem ; 
 int /*<<< orphan*/  y_mem ; 

void
u_memory(int *stats)
{
    static char *new = NULL;

    new = setup_buffer(new, 0);

    /* format the new line */
    summary_format(new, stats, memory_names);
    line_update(memory_buffer, new, x_mem, y_mem);
}