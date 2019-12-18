#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * d_error; } ;

/* Variables and functions */
 TYPE_1__ disk ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ufserr(const char *name)
{
	if (disk.d_error != NULL)
		warnx("%s: %s", name, disk.d_error);
	else if (errno)
		warn("%s", name);
}