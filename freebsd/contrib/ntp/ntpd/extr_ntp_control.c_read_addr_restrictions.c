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
typedef  scalar_t__ u_int ;
struct recvbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ctl_flushpkt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restrictlist4 ; 
 int /*<<< orphan*/  restrictlist6 ; 
 int /*<<< orphan*/  send_restrict_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void
read_addr_restrictions(
	struct recvbuf *	rbufp
)
{
	u_int idx;

	idx = 0;
	send_restrict_list(restrictlist4, FALSE, &idx);
	send_restrict_list(restrictlist6, TRUE, &idx);
	ctl_flushpkt(0);
}