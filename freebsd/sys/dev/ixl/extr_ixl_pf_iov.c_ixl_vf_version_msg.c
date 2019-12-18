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
typedef  int uint16_t ;
struct virtchnl_version_info {int /*<<< orphan*/  minor; int /*<<< orphan*/  major; } ;
struct ixl_vf {int /*<<< orphan*/  version; } ;
struct ixl_pf {int dummy; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ERR_PARAM ; 
 int /*<<< orphan*/  I40E_SUCCESS ; 
 int /*<<< orphan*/  VIRTCHNL_OP_VERSION ; 
 int /*<<< orphan*/  VIRTCHNL_VERSION_MAJOR ; 
 int /*<<< orphan*/  VIRTCHNL_VERSION_MINOR ; 
 int /*<<< orphan*/  i40e_send_vf_nack (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_send_vf_msg (struct ixl_pf*,struct ixl_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtchnl_version_info*,int) ; 

__attribute__((used)) static void
ixl_vf_version_msg(struct ixl_pf *pf, struct ixl_vf *vf, void *msg,
    uint16_t msg_size)
{
	struct virtchnl_version_info reply;

	if (msg_size != sizeof(struct virtchnl_version_info)) {
		i40e_send_vf_nack(pf, vf, VIRTCHNL_OP_VERSION,
		    I40E_ERR_PARAM);
		return;
	}

	vf->version = ((struct virtchnl_version_info *)msg)->minor;

	reply.major = VIRTCHNL_VERSION_MAJOR;
	reply.minor = VIRTCHNL_VERSION_MINOR;
	ixl_send_vf_msg(pf, vf, VIRTCHNL_OP_VERSION, I40E_SUCCESS, &reply,
	    sizeof(reply));
}