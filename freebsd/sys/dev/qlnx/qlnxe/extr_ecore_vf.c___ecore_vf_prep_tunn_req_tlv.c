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
typedef  int /*<<< orphan*/  u8 ;
struct vfpf_update_tunn_param_tlv {int tun_mode_update_mask; int tunn_mode; } ;
struct ecore_tunn_update_type {int /*<<< orphan*/  tun_cls; scalar_t__ b_mode_enabled; scalar_t__ b_update_mode; } ;
typedef  enum ecore_tunn_clss { ____Placeholder_ecore_tunn_clss } ecore_tunn_clss ;

/* Variables and functions */

__attribute__((used)) static void
__ecore_vf_prep_tunn_req_tlv(struct vfpf_update_tunn_param_tlv *p_req,
			     struct ecore_tunn_update_type *p_src,
			     enum ecore_tunn_clss mask, u8 *p_cls)
{
	if (p_src->b_update_mode) {
		p_req->tun_mode_update_mask |= (1 << mask);

		if (p_src->b_mode_enabled)
			p_req->tunn_mode |= (1 << mask);
	}

	*p_cls = p_src->tun_cls;
}