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
 int /*<<< orphan*/  carc_buffer ; 
 int /*<<< orphan*/ * carc_names ; 
 int /*<<< orphan*/  line_update (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  summary_format (char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x_carc ; 
 int /*<<< orphan*/  y_carc ; 

void
u_carc(int *stats)
{
    static char *new = NULL;

    new = setup_buffer(new, 0);

    if (carc_names == NULL)
	return;

    /* format the new line */
    summary_format(new, stats, carc_names);
    line_update(carc_buffer, new, x_carc, y_carc);
}