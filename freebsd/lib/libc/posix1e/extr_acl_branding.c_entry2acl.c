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
typedef  scalar_t__ acl_t ;
typedef  scalar_t__ acl_entry_t ;

/* Variables and functions */
 long _ACL_T_ALIGNMENT_BITS ; 

__attribute__((used)) static acl_t
entry2acl(acl_entry_t entry)
{
	acl_t aclp;

	aclp = (acl_t)(((long)entry >> _ACL_T_ALIGNMENT_BITS) << _ACL_T_ALIGNMENT_BITS);

	return (aclp);
}