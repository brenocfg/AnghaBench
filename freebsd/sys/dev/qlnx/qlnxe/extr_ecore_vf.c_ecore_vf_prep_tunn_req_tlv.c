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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct vfpf_update_tunn_param_tlv {int dummy; } ;
struct ecore_tunn_update_udp_port {int /*<<< orphan*/  port; scalar_t__ b_update_port; } ;
struct ecore_tunn_update_type {int dummy; } ;
typedef  enum ecore_tunn_clss { ____Placeholder_ecore_tunn_clss } ecore_tunn_clss ;

/* Variables and functions */
 int /*<<< orphan*/  __ecore_vf_prep_tunn_req_tlv (struct vfpf_update_tunn_param_tlv*,struct ecore_tunn_update_type*,int,int*) ; 

__attribute__((used)) static void
ecore_vf_prep_tunn_req_tlv(struct vfpf_update_tunn_param_tlv *p_req,
			   struct ecore_tunn_update_type *p_src,
			   enum ecore_tunn_clss mask, u8 *p_cls,
			   struct ecore_tunn_update_udp_port *p_port,
			   u8 *p_update_port, u16 *p_udp_port)
{
	if (p_port->b_update_port) {
		*p_update_port = 1;
		*p_udp_port = p_port->port;
	}

	__ecore_vf_prep_tunn_req_tlv(p_req, p_src, mask, p_cls);
}