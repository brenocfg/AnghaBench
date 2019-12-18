#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifmp_ring {int /*<<< orphan*/  can_drain; int /*<<< orphan*/  drain; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__* iflib_txq_t ;
struct TYPE_3__ {struct ifmp_ring* ift_br; } ;

/* Variables and functions */
 int /*<<< orphan*/  iflib_txq_can_drain ; 
 int /*<<< orphan*/  iflib_txq_drain ; 
 int /*<<< orphan*/  iflib_txq_drain_always ; 
 int /*<<< orphan*/  iflib_txq_drain_free ; 
 int /*<<< orphan*/  ifmp_ring_check_drainage (struct ifmp_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iflib_ifmp_purge(iflib_txq_t txq)
{
	struct ifmp_ring *r;

	r = txq->ift_br;
	r->drain = iflib_txq_drain_free;
	r->can_drain = iflib_txq_drain_always;

	ifmp_ring_check_drainage(r, r->size);

	r->drain = iflib_txq_drain;
	r->can_drain = iflib_txq_can_drain;
}