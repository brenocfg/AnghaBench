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
typedef  scalar_t__ mode_t ;

/* Variables and functions */
 int ENOTCAPABLE ; 
 int O_CREAT ; 
 int allowed_operations ; 
 int capflags ; 
 scalar_t__ capmode ; 
 int /*<<< orphan*/  caprightsp ; 
 int /*<<< orphan*/  dnvlist_get_binary (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dnvlist_get_number (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_get_number (int /*<<< orphan*/  const*,char*) ; 

__attribute__((used)) static int
fileargs_limit(const nvlist_t *oldlimits, const nvlist_t *newlimits)
{

	if (oldlimits != NULL)
		return (ENOTCAPABLE);

	capflags = (int)dnvlist_get_number(newlimits, "flags", 0);
	allowed_operations = (int)dnvlist_get_number(newlimits, "operations", 0);
	if ((capflags & O_CREAT) != 0)
		capmode = (mode_t)nvlist_get_number(newlimits, "mode");
	else
		capmode = 0;

	caprightsp = dnvlist_get_binary(newlimits, "cap_rights", NULL, NULL, 0);

	return (0);
}