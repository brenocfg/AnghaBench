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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ checksum1; scalar_t__ netfn_rs_lun; } ;
struct ipmb_dev {TYPE_1__ request; } ;

/* Variables and functions */

__attribute__((used)) static u8 ipmb_verify_checksum1(struct ipmb_dev *ipmb_dev, u8 rs_sa)
{
	/* The 8 lsb of the sum is 0 when the checksum is valid */
	return (rs_sa + ipmb_dev->request.netfn_rs_lun +
		ipmb_dev->request.checksum1);
}