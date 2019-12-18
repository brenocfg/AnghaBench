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
typedef  int /*<<< orphan*/  acl_type_t ;

/* Variables and functions */
 int ___acl_delete_fd (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _acl_type_unold (int /*<<< orphan*/ ) ; 

int
acl_delete_fd_np(int filedes, acl_type_t type)
{

	type = _acl_type_unold(type);
	return (___acl_delete_fd(filedes, type));
}