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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int netfn_rs_lun; } ;
struct ipmb_dev {scalar_t__ msg_idx; TYPE_1__ request; } ;

/* Variables and functions */
 scalar_t__ IPMB_REQUEST_LEN_MIN ; 
 int NETFN_RSP_BIT_MASK ; 
 scalar_t__ ipmb_verify_checksum1 (struct ipmb_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_ipmb_request(struct ipmb_dev *ipmb_dev, u8 rs_sa)
{
	if (ipmb_dev->msg_idx >= IPMB_REQUEST_LEN_MIN) {
		if (ipmb_verify_checksum1(ipmb_dev, rs_sa))
			return false;

		/*
		 * Check whether this is an IPMB request or
		 * response.
		 * The 6 MSB of netfn_rs_lun are dedicated to the netfn
		 * while the remaining bits are dedicated to the lun.
		 * If the LSB of the netfn is cleared, it is associated
		 * with an IPMB request.
		 * If the LSB of the netfn is set, it is associated with
		 * an IPMB response.
		 */
		if (!(ipmb_dev->request.netfn_rs_lun & NETFN_RSP_BIT_MASK))
			return true;
	}
	return false;
}