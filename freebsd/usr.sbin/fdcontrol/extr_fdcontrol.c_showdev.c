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
typedef  enum fd_drivetype { ____Placeholder_fd_drivetype } fd_drivetype ;

/* Variables and functions */
 int /*<<< orphan*/  getname (int,char const**,char const**) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 scalar_t__ verbose ; 

void
showdev(enum fd_drivetype type, const char *fname)
{
	const char *name, *descr;

	getname(type, &name, &descr);
	if (verbose)
		printf("%s: %s drive (%s)\n", fname, name, descr);
	else
		printf("%s\n", name);
}