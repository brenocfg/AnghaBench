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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lastline ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  summary_format (char*,int*,int /*<<< orphan*/ *) ; 
 char* swap_buffer ; 
 int /*<<< orphan*/ * swap_names ; 

void
i_swap(int *stats)
{
    swap_buffer = setup_buffer(swap_buffer, 0);

    if (swap_names == NULL)
	    return;

    fputs("\nSwap: ", stdout);
    lastline++;

    /* format and print the swap summary */
    summary_format(swap_buffer, stats, swap_names);
    fputs(swap_buffer, stdout);
}