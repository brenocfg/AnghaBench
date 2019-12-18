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
typedef  int /*<<< orphan*/  acl_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_NFS4 ; 
 int /*<<< orphan*/  _PC_ACL_NFS4 ; 
 int /*<<< orphan*/  acl_get_fd_np (int,int /*<<< orphan*/ ) ; 
 int fpathconf (int,int /*<<< orphan*/ ) ; 

acl_t
acl_get_fd(int fd)
{
	if (fpathconf(fd, _PC_ACL_NFS4) == 1)
		return (acl_get_fd_np(fd, ACL_TYPE_NFS4));

	return (acl_get_fd_np(fd, ACL_TYPE_ACCESS));
}