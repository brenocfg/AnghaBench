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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  ADD_U_INT32 (int /*<<< orphan*/ *,int) ; 
 char AUT_IPC ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

token_t *
au_to_ipc(char type, int id)
{
	token_t *t;
	u_char *dptr = NULL;

	GET_TOKEN_AREA(t, dptr, 2 * sizeof(u_char) + sizeof(u_int32_t));
	if (t == NULL)
		return (NULL);

	ADD_U_CHAR(dptr, AUT_IPC);
	ADD_U_CHAR(dptr, type);
	ADD_U_INT32(dptr, id);

	return (t);
}