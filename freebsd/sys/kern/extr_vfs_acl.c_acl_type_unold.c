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
 int ACL_TYPE_ACCESS ; 
#define  ACL_TYPE_ACCESS_OLD 129 
 int ACL_TYPE_DEFAULT ; 
#define  ACL_TYPE_DEFAULT_OLD 128 

__attribute__((used)) static int
acl_type_unold(int type)
{
	switch (type) {
	case ACL_TYPE_ACCESS_OLD:
		return (ACL_TYPE_ACCESS);

	case ACL_TYPE_DEFAULT_OLD:
		return (ACL_TYPE_DEFAULT);

	default:
		return (type);
	}
}