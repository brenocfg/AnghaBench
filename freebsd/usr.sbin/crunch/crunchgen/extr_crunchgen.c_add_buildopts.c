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
 int /*<<< orphan*/  add_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  buildopts ; 

void
add_buildopts(int argc, char **argv)
{
	int i;

	for (i = 1; i < argc; i++)
		add_string(&buildopts, argv[i]);
}