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
 size_t WRITE_PIPE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int ret_count ; 
 int /*<<< orphan*/ * slvpipe ; 
 scalar_t__ write (int /*<<< orphan*/ ,int*,int) ; 

void
report_count(int count)
{
	int type;

	type = ret_count;
	if (write(slvpipe[WRITE_PIPE], &type, sizeof(int)) < 0)
		err(1, "command pipe write for count type failed");

	if (write(slvpipe[WRITE_PIPE], &count, sizeof(int)) < 0)
		err(1, "command pipe write for count");
}