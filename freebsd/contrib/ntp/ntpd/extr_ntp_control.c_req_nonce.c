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
struct recvbuf {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_flushpkt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_putunqstr (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_nonce (struct recvbuf*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void req_nonce(
	struct recvbuf *	rbufp,
	int			restrict_mask
	)
{
	char	buf[64];

	generate_nonce(rbufp, buf, sizeof(buf));
	ctl_putunqstr("nonce", buf, strlen(buf));
	ctl_flushpkt(0);
}