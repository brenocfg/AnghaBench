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
struct nl_sock {int /*<<< orphan*/  s_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_CB_CUSTOM ; 
 int /*<<< orphan*/  NL_CB_SEQ_CHECK ; 
 int /*<<< orphan*/  nl_cb_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noop_seq_check ; 

void nl_socket_disable_seq_check(struct nl_sock *sk)
{
	nl_cb_set(sk->s_cb, NL_CB_SEQ_CHECK,
		  NL_CB_CUSTOM, noop_seq_check, NULL);
}