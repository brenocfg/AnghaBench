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

/* Variables and functions */
 scalar_t__ dst_addr ; 
 int recv_msg (int) ; 
 int send_msg (int) ; 

__attribute__((used)) static int sync_test(void)
{
	int ret;

	ret = dst_addr ? send_msg(16) : recv_msg(16);
	if (ret)
		return ret;

	return dst_addr ? recv_msg(16) : send_msg(16);
}