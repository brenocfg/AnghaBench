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
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  xmkstemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

int cmd__mktemp(int argc, const char **argv)
{
	if (argc != 2)
		usage("Expected 1 parameter defining the temporary file template");

	xmkstemp(xstrdup(argv[1]));

	return 0;
}