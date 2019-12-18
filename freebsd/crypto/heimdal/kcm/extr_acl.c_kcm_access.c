#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int kcm_operation ;
struct TYPE_8__ {scalar_t__ uid; scalar_t__ gid; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ kcm_client ;
typedef  TYPE_2__* kcm_ccache ;
struct TYPE_9__ {int flags; scalar_t__ uid; scalar_t__ gid; int mode; int /*<<< orphan*/  name; int /*<<< orphan*/  session; } ;

/* Variables and functions */
 scalar_t__ CLIENT_IS_ROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  KCM_ASSERT_VALID (TYPE_2__*) ; 
 int KCM_FLAGS_OWNER_IS_SYSTEM ; 
#define  KCM_OP_CHMOD 151 
#define  KCM_OP_CHOWN 150 
#define  KCM_OP_DESTROY 149 
#define  KCM_OP_GEN_NEW 148 
#define  KCM_OP_GET_CACHE_BY_UUID 147 
#define  KCM_OP_GET_CACHE_UUID_LIST 146 
#define  KCM_OP_GET_CRED_BY_UUID 145 
#define  KCM_OP_GET_CRED_UUID_LIST 144 
#define  KCM_OP_GET_DEFAULT_CACHE 143 
#define  KCM_OP_GET_INITIAL_TICKET 142 
#define  KCM_OP_GET_KDC_OFFSET 141 
#define  KCM_OP_GET_NAME 140 
#define  KCM_OP_GET_PRINCIPAL 139 
#define  KCM_OP_GET_TICKET 138 
#define  KCM_OP_INITIALIZE 137 
#define  KCM_OP_MOVE_CACHE 136 
#define  KCM_OP_NOOP 135 
#define  KCM_OP_REMOVE_CRED 134 
#define  KCM_OP_RESOLVE 133 
#define  KCM_OP_RETRIEVE 132 
#define  KCM_OP_SET_DEFAULT_CACHE 131 
#define  KCM_OP_SET_FLAGS 130 
#define  KCM_OP_SET_KDC_OFFSET 129 
#define  KCM_OP_STORE 128 
 scalar_t__ KRB5_FCC_PERM ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 scalar_t__ kcm_is_same_session (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcm_log (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcm_op2string (int) ; 

krb5_error_code
kcm_access(krb5_context context,
	   kcm_client *client,
	   kcm_operation opcode,
	   kcm_ccache ccache)
{
    int read_p = 0;
    int write_p = 0;
    uint16_t mask;
    krb5_error_code ret;

    KCM_ASSERT_VALID(ccache);

    switch (opcode) {
    case KCM_OP_INITIALIZE:
    case KCM_OP_DESTROY:
    case KCM_OP_STORE:
    case KCM_OP_REMOVE_CRED:
    case KCM_OP_SET_FLAGS:
    case KCM_OP_CHOWN:
    case KCM_OP_CHMOD:
    case KCM_OP_GET_INITIAL_TICKET:
    case KCM_OP_GET_TICKET:
    case KCM_OP_MOVE_CACHE:
    case KCM_OP_SET_DEFAULT_CACHE:
    case KCM_OP_SET_KDC_OFFSET:
	write_p = 1;
	read_p = 0;
	break;
    case KCM_OP_NOOP:
    case KCM_OP_GET_NAME:
    case KCM_OP_RESOLVE:
    case KCM_OP_GEN_NEW:
    case KCM_OP_RETRIEVE:
    case KCM_OP_GET_PRINCIPAL:
    case KCM_OP_GET_CRED_UUID_LIST:
    case KCM_OP_GET_CRED_BY_UUID:
    case KCM_OP_GET_CACHE_UUID_LIST:
    case KCM_OP_GET_CACHE_BY_UUID:
    case KCM_OP_GET_DEFAULT_CACHE:
    case KCM_OP_GET_KDC_OFFSET:
	write_p = 0;
	read_p = 1;
	break;
    default:
	ret = KRB5_FCC_PERM;
	goto out;
    }

    if (ccache->flags & KCM_FLAGS_OWNER_IS_SYSTEM) {
	/* System caches cannot be reinitialized or destroyed by users */
	if (opcode == KCM_OP_INITIALIZE ||
	    opcode == KCM_OP_DESTROY ||
	    opcode == KCM_OP_REMOVE_CRED ||
	    opcode == KCM_OP_MOVE_CACHE) {
	    ret = KRB5_FCC_PERM;
	    goto out;
	}

	/* Let root always read system caches */
	if (CLIENT_IS_ROOT(client)) {
	    ret = 0;
	    goto out;
	}
    }

    /* start out with "other" mask */
    mask = S_IROTH|S_IWOTH;

    /* root can do anything */
    if (CLIENT_IS_ROOT(client)) {
	if (read_p)
	    mask |= S_IRUSR|S_IRGRP|S_IROTH;
	if (write_p)
	    mask |= S_IWUSR|S_IWGRP|S_IWOTH;
    }
    /* same session same as owner */
    if (kcm_is_same_session(client, ccache->uid, ccache->session)) {
	if (read_p)
	    mask |= S_IROTH;
	if (write_p)
	    mask |= S_IWOTH;
    }
    /* owner */
    if (client->uid == ccache->uid) {
	if (read_p)
	    mask |= S_IRUSR;
	if (write_p)
	    mask |= S_IWUSR;
    }
    /* group */
    if (client->gid == ccache->gid) {
	if (read_p)
	    mask |= S_IRGRP;
	if (write_p)
	    mask |= S_IWGRP;
    }

    ret = (ccache->mode & mask) ? 0 : KRB5_FCC_PERM;

out:
    if (ret) {
	kcm_log(2, "Process %d is not permitted to call %s on cache %s",
		client->pid, kcm_op2string(opcode), ccache->name);
    }

    return ret;
}