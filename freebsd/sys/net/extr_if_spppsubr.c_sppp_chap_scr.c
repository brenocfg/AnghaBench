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
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ u_char ;
struct TYPE_2__ {int /*<<< orphan*/  name; scalar_t__ challenge; } ;
struct sppp {TYPE_1__ myauth; scalar_t__* confid; scalar_t__* pp_seq; } ;

/* Variables and functions */
 scalar_t__ AUTHKEYLEN ; 
 int /*<<< orphan*/  AUTHNAMELEN ; 
 int /*<<< orphan*/  CHAP_CHALLENGE ; 
 size_t IDX_CHAP ; 
 int /*<<< orphan*/  arc4random_buf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  chap ; 
 int /*<<< orphan*/  sppp_auth_send (int /*<<< orphan*/ *,struct sppp*,int /*<<< orphan*/ ,scalar_t__,int,char const*,size_t,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sppp_strnlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sppp_chap_scr(struct sppp *sp)
{
	u_long *ch;
	u_char clen;

	/* Compute random challenge. */
	ch = (u_long *)sp->myauth.challenge;
	arc4random_buf(ch, 4 * sizeof(*ch));
	clen = AUTHKEYLEN;

	sp->confid[IDX_CHAP] = ++sp->pp_seq[IDX_CHAP];

	sppp_auth_send(&chap, sp, CHAP_CHALLENGE, sp->confid[IDX_CHAP],
		       sizeof clen, (const char *)&clen,
		       (size_t)AUTHKEYLEN, sp->myauth.challenge,
		       (size_t)sppp_strnlen(sp->myauth.name, AUTHNAMELEN),
		       sp->myauth.name,
		       0);
}