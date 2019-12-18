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
struct pending {int pkt_len; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int comm_timer_get_mem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
waiting_udp_get_mem(struct pending* w)
{
	size_t s;
	s = sizeof(*w) + comm_timer_get_mem(w->timer) + w->pkt_len;
	return s;
}