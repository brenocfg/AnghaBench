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
typedef  int u_int32_t ;
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;
struct timeval {int tv_usec; int tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STRING (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT16 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ADD_U_INT32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AUT_OTHER_FILE32 ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

token_t *
au_to_file(const char *file, struct timeval tm)
{
	token_t *t;
	u_char *dptr = NULL;
	u_int16_t filelen;
	u_int32_t timems;

	filelen = strlen(file);
	filelen += 1;

	GET_TOKEN_AREA(t, dptr, sizeof(u_char) + 2 * sizeof(u_int32_t) +
	    sizeof(u_int16_t) + filelen);

	timems = tm.tv_usec/1000;

	ADD_U_CHAR(dptr, AUT_OTHER_FILE32);
	ADD_U_INT32(dptr, tm.tv_sec);
	ADD_U_INT32(dptr, timems);	/* We need time in ms. */
	ADD_U_INT16(dptr, filelen);
	ADD_STRING(dptr, file, filelen);

	return (t);
}