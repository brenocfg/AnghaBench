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
typedef  scalar_t__ uint16_t ;
struct ixl_vf {int dummy; } ;
struct ixl_pf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  VIRTCHNL_OP_RESET_VF ; 
 int /*<<< orphan*/  i40e_send_vf_nack (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_reset_vf (struct ixl_pf*,struct ixl_vf*) ; 

__attribute__((used)) static void
ixl_vf_reset_msg(struct ixl_pf *pf, struct ixl_vf *vf, void *msg,
    uint16_t msg_size)
{

	if (msg_size != 0) {
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_RESET_VF,
		    I40E_ERR_PARAM);
		return;
	}

	ixl_reset_vf(pf, vf);

	/* No response to a reset message. */
}