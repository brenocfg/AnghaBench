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

/* Variables and functions */
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  AUT_TRAILER ; 
 int /*<<< orphan*/  AUT_TRAILER_MAGIC ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

token_t *
au_to_trailer(int rec_size)
{
	token_t *t;
	u_char *dptr = NULL;
	u_int16_t magic = AUT_TRAILER_MAGIC;

	GET_TOKEN_AREA(t, dptr, sizeof(u_char) + sizeof(u_int16_t) +
	    sizeof(u_int32_t));

	ADD_U_CHAR(dptr, AUT_TRAILER);
	ADD_U_INT16(dptr, magic);
	ADD_U_INT32(dptr, rec_size);

	return (t);
}