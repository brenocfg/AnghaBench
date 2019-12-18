#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct eapol_state_machine {int remediation; TYPE_3__* eapol; } ;
struct eap_user {scalar_t__ remediation; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_4__ {int (* get_eap_user ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int,struct eap_user*) ;} ;
struct TYPE_6__ {TYPE_2__ conf; TYPE_1__ cb; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int,struct eap_user*) ; 

__attribute__((used)) static int eapol_sm_get_eap_user(void *ctx, const u8 *identity,
				 size_t identity_len, int phase2,
				 struct eap_user *user)
{
	struct eapol_state_machine *sm = ctx;
	int ret;

	ret = sm->eapol->cb.get_eap_user(sm->eapol->conf.ctx, identity,
					 identity_len, phase2, user);
	if (user->remediation)
		sm->remediation = 1;
	return ret;
}