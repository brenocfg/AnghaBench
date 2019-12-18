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
struct TYPE_2__ {int i; } ;
struct switch_val {TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTL8366S_SGCR ; 
 char RTL8366S_SGCR_MAX_LENGTH_1522 ; 
 char RTL8366S_SGCR_MAX_LENGTH_1536 ; 
 char RTL8366S_SGCR_MAX_LENGTH_1552 ; 
 char RTL8366S_SGCR_MAX_LENGTH_16000 ; 
 int /*<<< orphan*/  RTL8366S_SGCR_MAX_LENGTH_MASK ; 
 int rtl8366_smi_rmwr (struct rtl8366_smi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 
 struct rtl8366_smi* sw_to_rtl8366_smi (struct switch_dev*) ; 

__attribute__((used)) static int rtl8366s_sw_set_max_length(struct switch_dev *dev,
					const struct switch_attr *attr,
					struct switch_val *val)
{
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);
	char length_code;

	switch (val->value.i) {
		case 0:
			length_code = RTL8366S_SGCR_MAX_LENGTH_1522;
			break;
		case 1:
			length_code = RTL8366S_SGCR_MAX_LENGTH_1536;
			break;
		case 2:
			length_code = RTL8366S_SGCR_MAX_LENGTH_1552;
			break;
		case 3:
			length_code = RTL8366S_SGCR_MAX_LENGTH_16000;
			break;
		default:
			return -EINVAL;
	}

	return rtl8366_smi_rmwr(smi, RTL8366S_SGCR,
			RTL8366S_SGCR_MAX_LENGTH_MASK,
			length_code);
}