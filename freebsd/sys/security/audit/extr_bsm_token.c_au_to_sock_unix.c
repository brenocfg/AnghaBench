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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUT_SOCKUNIX ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

token_t *
au_to_sock_unix(struct sockaddr_un *so)
{
	token_t *t;
	u_char *dptr;

	GET_TOKEN_AREA(t, dptr, 3 * sizeof(u_char) + strlen(so->sun_path) + 1);

	ADD_U_CHAR(dptr, AUT_SOCKUNIX);
	/* BSM token has two bytes for family */
	ADD_U_CHAR(dptr, 0);
	ADD_U_CHAR(dptr, so->sun_family);
	ADD_STRING(dptr, so->sun_path, strlen(so->sun_path) + 1);

	return (t);
}