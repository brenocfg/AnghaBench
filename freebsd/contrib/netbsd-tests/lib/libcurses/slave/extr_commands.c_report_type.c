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
typedef  int returns_enum_t ;

/* Variables and functions */
 size_t WRITE_PIPE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * slvpipe ; 
 scalar_t__ write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void
report_type(returns_enum_t return_type)
{
	int type;

	type = return_type;
	if (write(slvpipe[WRITE_PIPE], &type, sizeof(int)) < 0)
		err(1, "command pipe write for status type failed");

}