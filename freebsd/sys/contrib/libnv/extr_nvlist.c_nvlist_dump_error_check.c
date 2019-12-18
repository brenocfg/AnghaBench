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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf (int,char*,int,char*,scalar_t__) ; 
 scalar_t__ nvlist_error (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool
nvlist_dump_error_check(const nvlist_t *nvl, int fd, int level)
{

	if (nvlist_error(nvl) != 0) {
		dprintf(fd, "%*serror: %d\n", level * 4, "",
		    nvlist_error(nvl));
		return (true);
	}

	return (false);
}