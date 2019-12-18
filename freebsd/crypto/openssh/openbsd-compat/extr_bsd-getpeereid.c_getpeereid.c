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
typedef  int /*<<< orphan*/  uid_t ;
struct ucred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  cred ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PEERCRED ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int*) ; 

int
getpeereid(int s, uid_t *euid, gid_t *gid)
{
	struct ucred cred;
	socklen_t len = sizeof(cred);

	if (getsockopt(s, SOL_SOCKET, SO_PEERCRED, &cred, &len) < 0)
		return (-1);
	*euid = cred.uid;
	*gid = cred.gid;

	return (0);
}