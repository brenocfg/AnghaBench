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
 char* carc_buffer ; 
 int /*<<< orphan*/ * carc_names ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lastline ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  summary_format (char*,int*,int /*<<< orphan*/ *) ; 

void
i_carc(int *stats)
{
    carc_buffer = setup_buffer(carc_buffer, 0);

    if (carc_names == NULL)
	return;

    fputs("\n     ", stdout);
    lastline++;

    /* format and print the memory summary */
    summary_format(carc_buffer, stats, carc_names);
    fputs(carc_buffer, stdout);
}