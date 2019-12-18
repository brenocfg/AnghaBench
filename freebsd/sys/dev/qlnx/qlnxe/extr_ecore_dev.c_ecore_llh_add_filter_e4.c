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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_llh_filter_e4_details {int enable; int value; int mode; scalar_t__ protocol_type; scalar_t__ hdr_sel; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ecore_llh_access_filter_e4 (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,scalar_t__,struct ecore_llh_filter_e4_details*,int) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_llh_add_filter_e4(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			u8 abs_ppfid, u8 filter_idx, u8 filter_prot_type,
			u32 high, u32 low)
{
	struct ecore_llh_filter_e4_details filter_details;

	filter_details.enable = 1;
	filter_details.value = ((u64)high << 32) | low;
	filter_details.hdr_sel = 0;
	filter_details.protocol_type = filter_prot_type;
	filter_details.mode = filter_prot_type ?
			      1 : /* protocol-based classification */
			      0;  /* MAC-address based classification */

	return ecore_llh_access_filter_e4(p_hwfn, p_ptt, abs_ppfid, filter_idx,
					  &filter_details,
					  true /* write access */);
}