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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  token_t ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_MEM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_U_INT16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUT_SOCKINET128 ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

token_t *
au_to_sock_inet128(struct sockaddr_in6 *so)
{
	token_t *t;
	u_char *dptr = NULL;

	GET_TOKEN_AREA(t, dptr, 3 * sizeof(u_char) + sizeof(u_int16_t) +
	    4 * sizeof(u_int32_t));

	ADD_U_CHAR(dptr, AUT_SOCKINET128);
	/*
	 * In BSD, sin6_family is one octet, but BSM defines the token to
	 * store two. So we copy in a 0 first.  XXXRW: Possibly should be
	 * conditionally compiled.
	 */
	ADD_U_CHAR(dptr, 0);
	ADD_U_CHAR(dptr, so->sin6_family);

	ADD_U_INT16(dptr, so->sin6_port);
	ADD_MEM(dptr, &so->sin6_addr, 4 * sizeof(uint32_t));

	return (t);
}