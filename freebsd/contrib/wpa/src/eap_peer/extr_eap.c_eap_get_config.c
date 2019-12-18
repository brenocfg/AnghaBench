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
struct eap_sm {int /*<<< orphan*/  eapol_ctx; TYPE_1__* eapol_cb; } ;
struct eap_peer_config {int dummy; } ;
struct TYPE_2__ {struct eap_peer_config* (* get_config ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct eap_peer_config* stub1 (int /*<<< orphan*/ ) ; 

struct eap_peer_config * eap_get_config(struct eap_sm *sm)
{
	return sm->eapol_cb->get_config(sm->eapol_ctx);
}