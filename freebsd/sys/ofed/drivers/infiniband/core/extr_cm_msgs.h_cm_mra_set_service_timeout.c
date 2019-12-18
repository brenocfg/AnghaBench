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
struct cm_mra_msg {int offset9; } ;

/* Variables and functions */

__attribute__((used)) static inline void cm_mra_set_service_timeout(struct cm_mra_msg *mra_msg,
					      u8 service_timeout)
{
	mra_msg->offset9 = (u8) ((mra_msg->offset9 & 0x07) |
				 (service_timeout << 3));
}