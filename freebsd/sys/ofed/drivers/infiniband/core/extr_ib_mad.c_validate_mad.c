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
typedef  scalar_t__ u32 ;
struct ib_mad_qp_info {TYPE_1__* qp; } ;
struct ib_mad_hdr {scalar_t__ base_version; scalar_t__ mgmt_class; scalar_t__ attr_id; scalar_t__ method; } ;
struct TYPE_2__ {scalar_t__ qp_num; } ;

/* Variables and functions */
 scalar_t__ IB_MGMT_BASE_VERSION ; 
 scalar_t__ IB_MGMT_CLASSPORTINFO_ATTR_ID ; 
 scalar_t__ IB_MGMT_CLASS_CM ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE ; 
 scalar_t__ IB_MGMT_CLASS_SUBN_LID_ROUTED ; 
 scalar_t__ IB_MGMT_METHOD_SEND ; 
 scalar_t__ OPA_MGMT_BASE_VERSION ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,char*) ; 

__attribute__((used)) static int validate_mad(const struct ib_mad_hdr *mad_hdr,
			const struct ib_mad_qp_info *qp_info,
			bool opa)
{
	int valid = 0;
	u32 qp_num = qp_info->qp->qp_num;

	/* Make sure MAD base version is understood */
	if (mad_hdr->base_version != IB_MGMT_BASE_VERSION &&
	    (!opa || mad_hdr->base_version != OPA_MGMT_BASE_VERSION)) {
		pr_err("MAD received with unsupported base version %d %s\n",
		       mad_hdr->base_version, opa ? "(opa)" : "");
		goto out;
	}

	/* Filter SMI packets sent to other than QP0 */
	if ((mad_hdr->mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED) ||
	    (mad_hdr->mgmt_class == IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE)) {
		if (qp_num == 0)
			valid = 1;
	} else {
		/* CM attributes other than ClassPortInfo only use Send method */
		if ((mad_hdr->mgmt_class == IB_MGMT_CLASS_CM) &&
		    (mad_hdr->attr_id != IB_MGMT_CLASSPORTINFO_ATTR_ID) &&
		    (mad_hdr->method != IB_MGMT_METHOD_SEND))
			goto out;
		/* Filter GSI packets sent to QP0 */
		if (qp_num != 0)
			valid = 1;
	}

out:
	return valid;
}