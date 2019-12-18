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
 int /*<<< orphan*/  try_to_run (int,int /*<<< orphan*/ ,char* const*,char*,char*) ; 

__attribute__((used)) static void
expect_success(int binary, char *pathfds)
{
	char * const env[] = { pathfds, NULL };
	try_to_run(binary, 0, env, "the hypotenuse of 3 and 4 is 5\n", "");
}