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
struct netmap_ring {int flags; int /*<<< orphan*/  ts; } ;

/* Variables and functions */
 int NR_TIMESTAMP ; 
 int /*<<< orphan*/  microtime (int /*<<< orphan*/ *) ; 
 scalar_t__ netmap_no_timestamp ; 

__attribute__((used)) static inline void
ring_timestamp_set(struct netmap_ring *ring)
{
	if (netmap_no_timestamp == 0 || ring->flags & NR_TIMESTAMP) {
		microtime(&ring->ts);
	}
}