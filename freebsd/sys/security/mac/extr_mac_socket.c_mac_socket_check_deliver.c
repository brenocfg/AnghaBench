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
struct socket {int /*<<< orphan*/  so_label; } ;
struct mbuf {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct socket*,struct mbuf*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ,struct mbuf*,struct label*) ; 
 struct label* mac_mbuf_to_label (struct mbuf*) ; 
 scalar_t__ mac_policy_count ; 
 int /*<<< orphan*/  socket_check_deliver ; 

int
mac_socket_check_deliver(struct socket *so, struct mbuf *m)
{
	struct label *label;
	int error;

	if (mac_policy_count == 0)
		return (0);

	label = mac_mbuf_to_label(m);

	MAC_POLICY_CHECK_NOSLEEP(socket_check_deliver, so, so->so_label, m,
	    label);
	MAC_CHECK_PROBE2(socket_check_deliver, error, so, m);

	return (error);
}