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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int udp_send_errno_needs_log (struct sockaddr*,int /*<<< orphan*/ ) ; 

int tcp_connect_errno_needs_log(struct sockaddr* addr, socklen_t addrlen)
{
	return udp_send_errno_needs_log(addr, addrlen);
}