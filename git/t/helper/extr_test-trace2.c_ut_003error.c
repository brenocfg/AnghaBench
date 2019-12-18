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
 int /*<<< orphan*/  error (char*,char const*) ; 

__attribute__((used)) static int ut_003error(int argc, const char **argv)
{
	int k;

	if (!argv[0] || !*argv[0])
		die("expect <error_message>");

	for (k = 0; k < argc; k++)
		error("%s", argv[k]);

	return 0;
}