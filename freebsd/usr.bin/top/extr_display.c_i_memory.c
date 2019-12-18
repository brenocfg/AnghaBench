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
 char* memory_buffer ; 
 int /*<<< orphan*/  memory_names ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  summary_format (char*,int*,int /*<<< orphan*/ ) ; 

void
i_memory(int *stats)
{
    memory_buffer = setup_buffer(memory_buffer, 0);

    fputs("\nMem: ", stdout);
    lastline++;

    /* format and print the memory summary */
    summary_format(memory_buffer, stats, memory_names);
    fputs(memory_buffer, stdout);
}