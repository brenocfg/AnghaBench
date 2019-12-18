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
struct ib_mad_hdr {scalar_t__ mgmt_class; int method; } ;

/* Variables and functions */
 scalar_t__ IB_MGMT_CLASS_SUBN_ADM ; 
 scalar_t__ IB_MGMT_CLASS_VENDOR_RANGE2_END ; 
 scalar_t__ IB_MGMT_CLASS_VENDOR_RANGE2_START ; 
#define  IB_SA_METHOD_GET_MULTI_RESP 130 
#define  IB_SA_METHOD_GET_TABLE 129 
#define  IB_SA_METHOD_GET_TABLE_RESP 128 

__attribute__((used)) static int is_rmpp_mad(struct ib_mad_hdr *mad_hdr)
{
	if (mad_hdr->mgmt_class == IB_MGMT_CLASS_SUBN_ADM) {
		switch (mad_hdr->method) {
		case IB_SA_METHOD_GET_TABLE:
		case IB_SA_METHOD_GET_TABLE_RESP:
		case IB_SA_METHOD_GET_MULTI_RESP:
			return 1;
		default:
			break;
		}
	} else if ((mad_hdr->mgmt_class >= IB_MGMT_CLASS_VENDOR_RANGE2_START) &&
		   (mad_hdr->mgmt_class <= IB_MGMT_CLASS_VENDOR_RANGE2_END))
		return 1;

	return 0;
}