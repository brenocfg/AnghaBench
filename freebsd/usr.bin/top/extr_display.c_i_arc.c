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
 char* arc_buffer ; 
 int /*<<< orphan*/ * arc_names ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lastline ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  summary_format (char*,int*,int /*<<< orphan*/ *) ; 

void
i_arc(int *stats)
{
    arc_buffer = setup_buffer(arc_buffer, 0);

    if (arc_names == NULL)
	return;

    fputs("\nARC: ", stdout);
    lastline++;

    /* format and print the memory summary */
    summary_format(arc_buffer, stats, arc_names);
    fputs(arc_buffer, stdout);
}