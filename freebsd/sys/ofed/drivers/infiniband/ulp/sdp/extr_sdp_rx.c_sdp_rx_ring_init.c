#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  destroyed_lock; scalar_t__ destroyed; int /*<<< orphan*/ * buffer; } ;
struct sdp_sock {TYPE_1__ rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 

void
sdp_rx_ring_init(struct sdp_sock *ssk)
{
	ssk->rx_ring.buffer = NULL;
	ssk->rx_ring.destroyed = 0;
	rw_init(&ssk->rx_ring.destroyed_lock, "sdp rx lock");
}