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
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int __acl_delete_link (char const*,int /*<<< orphan*/ ) ; 

int
acl_delete_def_link_np(const char *path_p)
{

	return (__acl_delete_link(path_p, ACL_TYPE_DEFAULT));
}