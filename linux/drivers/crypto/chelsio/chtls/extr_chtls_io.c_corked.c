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
struct tcp_sock {int nonagle; } ;

/* Variables and functions */
 int MSG_MORE ; 
 int TCP_NAGLE_CORK ; 

__attribute__((used)) static bool corked(const struct tcp_sock *tp, int flags)
{
	return (flags & MSG_MORE) || (tp->nonagle & TCP_NAGLE_CORK);
}