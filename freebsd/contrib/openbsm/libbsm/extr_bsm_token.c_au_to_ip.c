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
struct ip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_MEM (int /*<<< orphan*/ *,struct ip*,int) ; 
 int /*<<< orphan*/  ADD_U_CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUT_IP ; 
 int /*<<< orphan*/  GET_TOKEN_AREA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

token_t *
au_to_ip(struct ip *ip)
{
	token_t *t;
	u_char *dptr = NULL;

	GET_TOKEN_AREA(t, dptr, sizeof(u_char) + sizeof(struct ip));
	if (t == NULL)
		return (NULL);

	ADD_U_CHAR(dptr, AUT_IP);
	ADD_MEM(dptr, ip, sizeof(struct ip));

	return (t);
}