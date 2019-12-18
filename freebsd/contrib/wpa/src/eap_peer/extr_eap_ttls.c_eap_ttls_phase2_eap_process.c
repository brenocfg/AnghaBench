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
struct eap_ttls_data {int /*<<< orphan*/  phase2_priv; TYPE_1__* phase2_method; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {scalar_t__ methodState; scalar_t__ decision; } ;
struct eap_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  iret ;
struct TYPE_2__ {struct wpabuf* (* process ) (struct eap_sm*,int /*<<< orphan*/ ,struct eap_method_ret*,struct wpabuf*) ;} ;

/* Variables and functions */
 scalar_t__ DECISION_COND_SUCC ; 
 scalar_t__ DECISION_FAIL ; 
 scalar_t__ DECISION_UNCOND_SUCC ; 
 scalar_t__ METHOD_DONE ; 
 scalar_t__ METHOD_MAY_CONT ; 
 int /*<<< orphan*/  os_memset (struct eap_method_ret*,int /*<<< orphan*/ ,int) ; 
 struct wpabuf* stub1 (struct eap_sm*,int /*<<< orphan*/ ,struct eap_method_ret*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,struct eap_hdr*,size_t) ; 

__attribute__((used)) static int eap_ttls_phase2_eap_process(struct eap_sm *sm,
				       struct eap_ttls_data *data,
				       struct eap_method_ret *ret,
				       struct eap_hdr *hdr, size_t len,
				       struct wpabuf **resp)
{
	struct wpabuf msg;
	struct eap_method_ret iret;

	os_memset(&iret, 0, sizeof(iret));
	wpabuf_set(&msg, hdr, len);
	*resp = data->phase2_method->process(sm, data->phase2_priv, &iret,
					     &msg);
	if ((iret.methodState == METHOD_DONE ||
	     iret.methodState == METHOD_MAY_CONT) &&
	    (iret.decision == DECISION_UNCOND_SUCC ||
	     iret.decision == DECISION_COND_SUCC ||
	     iret.decision == DECISION_FAIL)) {
		ret->methodState = iret.methodState;
		ret->decision = iret.decision;
	}

	return 0;
}