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
struct nl_sock {int dummy; } ;
struct genlmsghdr {int cmd; int version; } ;
typedef  int /*<<< orphan*/  hdr ;

/* Variables and functions */
 int nl_send_simple (struct nl_sock*,int,int,struct genlmsghdr*,int) ; 

int genl_send_simple(struct nl_sock *sk, int family, int cmd,
		     int version, int flags)
{
	struct genlmsghdr hdr = {
		.cmd = cmd,
		.version = version,
	};

	return nl_send_simple(sk, family, flags, &hdr, sizeof(hdr));
}