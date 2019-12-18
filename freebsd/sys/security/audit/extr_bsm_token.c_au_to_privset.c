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
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STRING (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT16 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  AUT_PRIV ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 

token_t *
au_to_privset(char *privtypestr, char *privstr)
{
	u_int16_t	 type_len, priv_len;
	u_char		*dptr;
	token_t		*t;

	type_len = strlen(privtypestr) + 1;
	priv_len = strlen(privstr) + 1;
	GET_TOKEN_AREA(t, dptr, sizeof(u_char) + sizeof(u_int16_t) +
	    sizeof(u_int16_t) + type_len + priv_len);

	ADD_U_CHAR(dptr, AUT_PRIV);
	ADD_U_INT16(dptr, type_len);
	ADD_STRING(dptr, privtypestr, type_len);
	ADD_U_INT16(dptr, priv_len);
	ADD_STRING(dptr, privstr, priv_len);
	return (t);
}