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
struct acl {int dummy; } ;
typedef  int mode_t ;

/* Variables and functions */
 int ACL_OVERRIDE_MASK ; 
 int ACL_PRESERVE_MASK ; 
 int acl_posix1e_acl_to_mode (struct acl*) ; 

mode_t
acl_posix1e_newfilemode(mode_t cmode, struct acl *dacl)
{
	mode_t mode;

	mode = cmode;
	/*
	 * The current composition policy is that a permission bit must be
	 * set in *both* the ACL and the requested creation mode for it to
	 * appear in the resulting mode/ACL.  First clear any possibly
	 * effected bits, then reconstruct.
	 */
	mode &= ACL_PRESERVE_MASK;
	mode |= (ACL_OVERRIDE_MASK & cmode & acl_posix1e_acl_to_mode(dacl));

	return (mode);
}