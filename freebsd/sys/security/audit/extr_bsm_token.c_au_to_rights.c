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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;
struct TYPE_3__ {int /*<<< orphan*/ * cr_rights; } ;
typedef  TYPE_1__ cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUT_RIGHTS ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int nitems (int /*<<< orphan*/ *) ; 

token_t *
au_to_rights(cap_rights_t *rightsp)
{
	token_t *t;
	u_char *dptr;
	int i;

	GET_TOKEN_AREA(t, dptr, sizeof(u_char) + sizeof(*rightsp));

	ADD_U_CHAR(dptr, AUT_RIGHTS);
	for (i = 0; i < nitems(rightsp->cr_rights); i++)
		ADD_U_INT64(dptr, rightsp->cr_rights[i]);

	return (t);
}