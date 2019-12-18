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
typedef  int /*<<< orphan*/  xuc ;
typedef  int /*<<< orphan*/  uid_t ;
struct xucred {scalar_t__ cr_version; int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOCAL_PEERCRED ; 
 scalar_t__ XUCRED_VERSION ; 
 int _getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xucred*,int*) ; 
 int /*<<< orphan*/  errno ; 

int
getpeereid(int s, uid_t *euid, gid_t *egid)
{
	struct xucred xuc;
	socklen_t xuclen;
	int error;

	xuclen = sizeof(xuc);
	error = _getsockopt(s, 0, LOCAL_PEERCRED, &xuc, &xuclen);
	if (error != 0)
		return (error);
	if (xuc.cr_version != XUCRED_VERSION) {
		errno = EINVAL;
		return (-1);
	}
	*euid = xuc.cr_uid;
	*egid = xuc.cr_gid;
	return (0);
}