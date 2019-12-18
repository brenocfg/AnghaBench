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
struct iwi_softc {int dummy; } ;
struct iwi_cmd_ring {scalar_t__ next; scalar_t__ cur; scalar_t__ queued; } ;

/* Variables and functions */

__attribute__((used)) static void
iwi_reset_cmd_ring(struct iwi_softc *sc, struct iwi_cmd_ring *ring)
{
	ring->queued = 0;
	ring->cur = ring->next = 0;
}