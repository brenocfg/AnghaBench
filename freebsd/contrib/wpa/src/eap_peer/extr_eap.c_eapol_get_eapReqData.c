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
struct wpabuf {int dummy; } ;
struct eap_sm {int /*<<< orphan*/  eapol_ctx; TYPE_1__* eapol_cb; } ;
struct TYPE_2__ {struct wpabuf* (* get_eapReqData ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct wpabuf* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eapol_get_eapReqData(struct eap_sm *sm)
{
	return sm->eapol_cb->get_eapReqData(sm->eapol_ctx);
}