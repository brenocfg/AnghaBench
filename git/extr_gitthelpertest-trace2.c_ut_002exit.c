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
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ get_i (int*,char const*) ; 

__attribute__((used)) static int ut_002exit(int argc, const char **argv)
{
	int rc;

	if (get_i(&rc, argv[0]))
		die("expect <exit_code>");

	exit(rc);
}