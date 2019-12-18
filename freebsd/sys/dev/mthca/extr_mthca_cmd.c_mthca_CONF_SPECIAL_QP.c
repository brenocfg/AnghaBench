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
typedef  int /*<<< orphan*/  u32 ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CONF_SPECIAL_QP ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_B ; 
 int EINVAL ; 
#define  IB_QPT_GSI 131 
#define  IB_QPT_RAW_ETHERTYPE 130 
#define  IB_QPT_RAW_IPV6 129 
#define  IB_QPT_SMI 128 
 int mthca_cmd (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mthca_CONF_SPECIAL_QP(struct mthca_dev *dev, int type, u32 qpn)
{
	u8 op_mod;

	switch (type) {
	case IB_QPT_SMI:
		op_mod = 0;
		break;
	case IB_QPT_GSI:
		op_mod = 1;
		break;
	case IB_QPT_RAW_IPV6:
		op_mod = 2;
		break;
	case IB_QPT_RAW_ETHERTYPE:
		op_mod = 3;
		break;
	default:
		return -EINVAL;
	}

	return mthca_cmd(dev, 0, qpn, op_mod, CMD_CONF_SPECIAL_QP,
			 CMD_TIME_CLASS_B);
}