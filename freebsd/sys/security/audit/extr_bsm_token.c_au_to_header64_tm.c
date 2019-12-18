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
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;
struct timeval {int tv_usec; int tv_sec; } ;
typedef  int /*<<< orphan*/  au_event_t ;
typedef  int /*<<< orphan*/  au_emod_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ADD_U_INT64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AUDIT_HEADER_VERSION_OPENBSM ; 
 int /*<<< orphan*/  AUT_HEADER64 ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

token_t *
au_to_header64_tm(int rec_size, au_event_t e_type, au_emod_t e_mod,
    struct timeval tm)
{
	token_t *t;
	u_char *dptr = NULL;
	u_int32_t timems;

	GET_TOKEN_AREA(t, dptr, sizeof(u_char) + sizeof(u_int32_t) +
	    sizeof(u_char) + 2 * sizeof(u_int16_t) + 2 * sizeof(u_int64_t));

	ADD_U_CHAR(dptr, AUT_HEADER64);
	ADD_U_INT32(dptr, rec_size);
	ADD_U_CHAR(dptr, AUDIT_HEADER_VERSION_OPENBSM);
	ADD_U_INT16(dptr, e_type);
	ADD_U_INT16(dptr, e_mod);

	timems = tm.tv_usec/1000;
	/* Add the timestamp */
	ADD_U_INT64(dptr, tm.tv_sec);
	ADD_U_INT64(dptr, timems);	/* We need time in ms. */

	return (t);
}