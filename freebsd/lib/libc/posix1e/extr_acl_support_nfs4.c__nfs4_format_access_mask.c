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
typedef  int /*<<< orphan*/  acl_perm_t ;

/* Variables and functions */
 int /*<<< orphan*/  a_access_masks ; 
 int format_flags_compact (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int format_flags_verbose (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
_nfs4_format_access_mask(char *str, size_t size, acl_perm_t var, int verbose)
{

	if (verbose)
		return (format_flags_verbose(str, size, var, a_access_masks));

	return (format_flags_compact(str, size, var, a_access_masks));
}