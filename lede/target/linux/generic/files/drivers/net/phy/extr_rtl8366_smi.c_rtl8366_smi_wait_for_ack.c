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
typedef  scalar_t__ u32 ;
struct rtl8366_smi {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int RTL8366_SMI_ACK_RETRY_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtl8366_smi_read_bits (struct rtl8366_smi*,int,scalar_t__*) ; 

__attribute__((used)) static int rtl8366_smi_wait_for_ack(struct rtl8366_smi *smi)
{
	int retry_cnt;

	retry_cnt = 0;
	do {
		u32 ack;

		rtl8366_smi_read_bits(smi, 1, &ack);
		if (ack == 0)
			break;

		if (++retry_cnt > RTL8366_SMI_ACK_RETRY_COUNT) {
			dev_err(smi->parent, "ACK timeout\n");
			return -ETIMEDOUT;
		}
	} while (1);

	return 0;
}