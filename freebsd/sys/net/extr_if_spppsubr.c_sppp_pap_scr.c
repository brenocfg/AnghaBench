#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct TYPE_2__ {int /*<<< orphan*/  secret; int /*<<< orphan*/  name; } ;
struct sppp {TYPE_1__ myauth; scalar_t__* confid; scalar_t__* pp_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHKEYLEN ; 
 int /*<<< orphan*/  AUTHNAMELEN ; 
 size_t IDX_PAP ; 
 int /*<<< orphan*/  PAP_REQ ; 
 int /*<<< orphan*/  pap ; 
 int /*<<< orphan*/  sppp_auth_send (int /*<<< orphan*/ *,struct sppp*,int /*<<< orphan*/ ,scalar_t__,int,char const*,size_t,int /*<<< orphan*/ ,int,char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sppp_strnlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sppp_pap_scr(struct sppp *sp)
{
	u_char idlen, pwdlen;

	sp->confid[IDX_PAP] = ++sp->pp_seq[IDX_PAP];
	pwdlen = sppp_strnlen(sp->myauth.secret, AUTHKEYLEN);
	idlen = sppp_strnlen(sp->myauth.name, AUTHNAMELEN);

	sppp_auth_send(&pap, sp, PAP_REQ, sp->confid[IDX_PAP],
		       sizeof idlen, (const char *)&idlen,
		       (size_t)idlen, sp->myauth.name,
		       sizeof pwdlen, (const char *)&pwdlen,
		       (size_t)pwdlen, sp->myauth.secret,
		       0);
}