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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct vio_dev {int dummy; } ;

/* Variables and functions */
 int ibmvtpm_send_crq_word (struct vio_dev*,int) ; 

__attribute__((used)) static int ibmvtpm_send_crq(struct vio_dev *vdev,
		u8 valid, u8 msg, u16 len, u32 data)
{
	u64 w1 = ((u64)valid << 56) | ((u64)msg << 48) | ((u64)len << 32) |
		(u64)data;
	return ibmvtpm_send_crq_word(vdev, w1);
}