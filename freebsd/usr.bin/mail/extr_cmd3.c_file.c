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
 int /*<<< orphan*/  announce () ; 
 int /*<<< orphan*/  newfileinfo (int /*<<< orphan*/ ) ; 
 scalar_t__ setfile (char*) ; 

int
file(char **argv)
{

	if (argv[0] == NULL) {
		newfileinfo(0);
		return (0);
	}
	if (setfile(*argv) < 0)
		return (1);
	announce();
	return (0);
}