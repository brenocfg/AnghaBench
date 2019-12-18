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
 int /*<<< orphan*/  crunch_file (int /*<<< orphan*/ ) ; 
 int file_count ; 
 int /*<<< orphan*/ * file_list ; 
 int /*<<< orphan*/  insert_before () ; 

__attribute__((used)) static void
crunch_all_files(void)
{
	int i;
	
	for (i = 0; i < file_count; i++)
		crunch_file(file_list[i]);
	insert_before();
}