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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;
struct ipc_perm {int /*<<< orphan*/  key; int /*<<< orphan*/  seq; int /*<<< orphan*/  mode; int /*<<< orphan*/  cgid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUT_IPC_PERM ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

token_t *
au_to_ipc_perm(struct ipc_perm *perm)
{
	token_t *t;
	u_char *dptr = NULL;
	u_int16_t pad0 = 0;

	GET_TOKEN_AREA(t, dptr, sizeof(u_char) + 12 * sizeof(u_int16_t) +
	    sizeof(u_int32_t));

	ADD_U_CHAR(dptr, AUT_IPC_PERM);

	/*
	 * Systems vary significantly in what types they use in struct
	 * ipc_perm; at least a few still use 16-bit uid's and gid's, so
	 * allow for that, as BSM define 32-bit values here.
	 * Some systems define the sizes for ipc_perm members as 2 bytes;
	 * BSM defines 4 so pad with 0.
	 *
	 * XXXRW: Possibly shoulid be conditionally compiled, and more cases
	 * need to be handled.
	 */
	if (sizeof(perm->uid) != sizeof(u_int32_t)) {
		ADD_U_INT16(dptr, pad0);
		ADD_U_INT16(dptr, perm->uid);
		ADD_U_INT16(dptr, pad0);
		ADD_U_INT16(dptr, perm->gid);
		ADD_U_INT16(dptr, pad0);
		ADD_U_INT16(dptr, perm->cuid);
		ADD_U_INT16(dptr, pad0);
		ADD_U_INT16(dptr, perm->cgid);
	} else {
		ADD_U_INT32(dptr, perm->uid);
		ADD_U_INT32(dptr, perm->gid);
		ADD_U_INT32(dptr, perm->cuid);
		ADD_U_INT32(dptr, perm->cgid);
	}

	ADD_U_INT16(dptr, pad0);
	ADD_U_INT16(dptr, perm->mode);

	ADD_U_INT16(dptr, pad0);

	ADD_U_INT16(dptr, perm->seq);

	ADD_U_INT32(dptr, perm->key);

	return (t);
}