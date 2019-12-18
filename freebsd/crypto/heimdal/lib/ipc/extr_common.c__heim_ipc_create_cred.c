#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  void* pid_t ;
typedef  TYPE_1__* heim_icred ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_4__ {void* session; void* pid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* calloc (int,int) ; 

int
_heim_ipc_create_cred(uid_t uid, gid_t gid, pid_t pid, pid_t session, heim_icred *cred)
{
    *cred = calloc(1, sizeof(**cred));
    if (*cred == NULL)
	return ENOMEM;
    (*cred)->uid = uid;
    (*cred)->gid = gid;
    (*cred)->pid = pid;
    (*cred)->session = session;
    return 0;
}