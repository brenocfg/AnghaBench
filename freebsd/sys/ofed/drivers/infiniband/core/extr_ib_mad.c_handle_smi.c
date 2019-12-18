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
struct ib_wc {int dummy; } ;
struct ib_mad_qp_info {int dummy; } ;
struct ib_mad_private {scalar_t__ mad; } ;
struct ib_mad_port_private {int dummy; } ;
struct ib_mad_hdr {scalar_t__ base_version; scalar_t__ class_version; } ;
typedef  enum smi_action { ____Placeholder_smi_action } smi_action ;

/* Variables and functions */
 scalar_t__ OPA_MGMT_BASE_VERSION ; 
 scalar_t__ OPA_SMI_CLASS_VERSION ; 
 int handle_ib_smi (struct ib_mad_port_private*,struct ib_mad_qp_info*,struct ib_wc*,int,struct ib_mad_private*,struct ib_mad_private*) ; 
 int handle_opa_smi (struct ib_mad_port_private*,struct ib_mad_qp_info*,struct ib_wc*,int,struct ib_mad_private*,struct ib_mad_private*) ; 

__attribute__((used)) static enum smi_action
handle_smi(struct ib_mad_port_private *port_priv,
	   struct ib_mad_qp_info *qp_info,
	   struct ib_wc *wc,
	   int port_num,
	   struct ib_mad_private *recv,
	   struct ib_mad_private *response,
	   bool opa)
{
	struct ib_mad_hdr *mad_hdr = (struct ib_mad_hdr *)recv->mad;

	if (opa && mad_hdr->base_version == OPA_MGMT_BASE_VERSION &&
	    mad_hdr->class_version == OPA_SMI_CLASS_VERSION)
		return handle_opa_smi(port_priv, qp_info, wc, port_num, recv,
				      response);

	return handle_ib_smi(port_priv, qp_info, wc, port_num, recv, response);
}