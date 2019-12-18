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
struct TYPE_2__ {int /*<<< orphan*/  rc_free; int /*<<< orphan*/  rc_num_maps_alloced; } ;
struct tcp_rack {scalar_t__ rc_free_cnt; TYPE_1__ r_ctl; } ;
struct rack_sendmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 struct rack_sendmap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct rack_sendmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_tnext ; 
 int /*<<< orphan*/  rack_to_alloc ; 
 int /*<<< orphan*/  rack_to_alloc_emerg ; 
 int /*<<< orphan*/  rack_zone ; 
 struct rack_sendmap* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rack_sendmap *
rack_alloc(struct tcp_rack *rack)
{
	struct rack_sendmap *rsm;

	rsm = uma_zalloc(rack_zone, M_NOWAIT);
	if (rsm) {
		rack->r_ctl.rc_num_maps_alloced++;
		counter_u64_add(rack_to_alloc, 1);
		return (rsm);
	}
	if (rack->rc_free_cnt) {
		counter_u64_add(rack_to_alloc_emerg, 1);
		rsm = TAILQ_FIRST(&rack->r_ctl.rc_free);
		TAILQ_REMOVE(&rack->r_ctl.rc_free, rsm, r_tnext);
		rack->rc_free_cnt--;
		return (rsm);
	}
	return (NULL);
}