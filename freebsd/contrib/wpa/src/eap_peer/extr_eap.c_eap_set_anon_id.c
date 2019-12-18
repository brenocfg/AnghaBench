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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int /*<<< orphan*/  eapol_ctx; TYPE_1__* eapol_cb; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_anon_id ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

void eap_set_anon_id(struct eap_sm *sm, const u8 *id, size_t len)
{
	if (sm->eapol_cb->set_anon_id)
		sm->eapol_cb->set_anon_id(sm->eapol_ctx, id, len);
}