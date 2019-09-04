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
 int merge_branch () ; 
 int /*<<< orphan*/  stage_random_files (char**) ; 

__attribute__((used)) static int merge_staged_files(char *staged_files[])
{
	stage_random_files(staged_files);
	return merge_branch();
}