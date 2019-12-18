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
 int /*<<< orphan*/  arc_buffer ; 
 int /*<<< orphan*/ * arc_names ; 
 int /*<<< orphan*/  line_update (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  summary_format (char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x_arc ; 
 int /*<<< orphan*/  y_arc ; 

void
u_arc(int *stats)
{
    static char *new = NULL;

    new = setup_buffer(new, 0);

    if (arc_names == NULL)
	return;

    /* format the new line */
    summary_format(new, stats, arc_names);
    line_update(arc_buffer, new, x_arc, y_arc);
}