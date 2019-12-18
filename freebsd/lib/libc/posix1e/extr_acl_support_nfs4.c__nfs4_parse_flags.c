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
typedef  int acl_flag_t ;

/* Variables and functions */
 int /*<<< orphan*/  a_flags ; 
 int parse_flags_compact (char const*,int*,int /*<<< orphan*/ ,char*) ; 
 int parse_flags_verbose (char const*,int*,int /*<<< orphan*/ ,char*,int*) ; 

int
_nfs4_parse_flags(const char *str, acl_flag_t *flags)
{
	int error, try_compact;
	int tmpflags;

	error = parse_flags_verbose(str, &tmpflags, a_flags, "flags", &try_compact);
	if (error && try_compact)
		error = parse_flags_compact(str, &tmpflags, a_flags, "flags");

	*flags = tmpflags;

	return (error);
}