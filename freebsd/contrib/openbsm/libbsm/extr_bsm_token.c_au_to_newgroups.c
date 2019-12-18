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
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ADD_U_INT32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUT_NEWGROUPS ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

token_t *
au_to_newgroups(u_int16_t n, gid_t *groups)
{
	token_t *t;
	u_char *dptr = NULL;
	int i;

	GET_TOKEN_AREA(t, dptr, sizeof(u_char) + sizeof(u_int16_t) +
	    n * sizeof(u_int32_t));
	if (t == NULL)
		return (NULL);

	ADD_U_CHAR(dptr, AUT_NEWGROUPS);
	ADD_U_INT16(dptr, n);
	for (i = 0; i < n; i++)
		ADD_U_INT32(dptr, groups[i]);

	return (t);
}