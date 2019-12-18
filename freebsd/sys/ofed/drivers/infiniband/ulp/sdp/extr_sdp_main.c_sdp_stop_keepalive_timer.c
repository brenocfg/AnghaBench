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
struct socket {int dummy; } ;
struct sdp_sock {int /*<<< orphan*/  keep2msl; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct sdp_sock* sdp_sk (struct socket*) ; 

__attribute__((used)) static void
sdp_stop_keepalive_timer(struct socket *so)
{
	struct sdp_sock *ssk;

	ssk = sdp_sk(so);
	callout_stop(&ssk->keep2msl);
}