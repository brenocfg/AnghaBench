#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_3__ {int /*<<< orphan*/ * at_addr; int /*<<< orphan*/  at_type; int /*<<< orphan*/  at_port; } ;
typedef  TYPE_1__ au_tid_addr_t ;
typedef  int /*<<< orphan*/  au_id_t ;
typedef  int /*<<< orphan*/  au_asid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_MEM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUT_SUBJECT64_EX ; 
 int /*<<< orphan*/  AU_IPv4 ; 
 int /*<<< orphan*/  AU_IPv6 ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  errno ; 

token_t *
au_to_subject64_ex(au_id_t auid, uid_t euid, gid_t egid, uid_t ruid,
    gid_t rgid, pid_t pid, au_asid_t sid, au_tid_addr_t *tid)
{
	token_t *t;
	u_char *dptr = NULL;

	if (tid->at_type == AU_IPv4)
		GET_TOKEN_AREA(t, dptr, sizeof(u_char) +
		    7 * sizeof(u_int32_t) + sizeof(u_int64_t) +
		    2 * sizeof(u_int32_t));
	else if (tid->at_type == AU_IPv6)
		GET_TOKEN_AREA(t, dptr, sizeof(u_char) +
		    7 * sizeof(u_int32_t) + sizeof(u_int64_t) +
		    5 * sizeof(u_int32_t));
	else {
		errno = EINVAL;
		return (NULL);
	}
	if (t == NULL)
		return (NULL);

	ADD_U_CHAR(dptr, AUT_SUBJECT64_EX);
	ADD_U_INT32(dptr, auid);
	ADD_U_INT32(dptr, euid);
	ADD_U_INT32(dptr, egid);
	ADD_U_INT32(dptr, ruid);
	ADD_U_INT32(dptr, rgid);
	ADD_U_INT32(dptr, pid);
	ADD_U_INT32(dptr, sid);
	ADD_U_INT64(dptr, tid->at_port);
	ADD_U_INT32(dptr, tid->at_type);
	if (tid->at_type == AU_IPv6)
		ADD_MEM(dptr, &tid->at_addr[0], 4 * sizeof(u_int32_t));
	else
		ADD_MEM(dptr, &tid->at_addr[0], sizeof(u_int32_t));

	return (t);
}