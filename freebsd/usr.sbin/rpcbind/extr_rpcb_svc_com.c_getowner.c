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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  SVCXPRT ;

/* Variables and functions */
 scalar_t__ __rpc_get_local_uid (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static char *
getowner(SVCXPRT *transp, char *owner, size_t ownersize)
{
	uid_t uid;
 
	if (__rpc_get_local_uid(transp, &uid) < 0)
                strlcpy(owner, "unknown", ownersize);
	else if (uid == 0)
		strlcpy(owner, "superuser", ownersize);
	else
		snprintf(owner, ownersize, "%d", uid);  

	return owner;
}