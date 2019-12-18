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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ rc_num_split_allocs; } ;
struct tcp_rack {scalar_t__ do_detection; int alloc_limit_reported; TYPE_1__ r_ctl; } ;
struct rack_sendmap {scalar_t__ r_limit_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 struct rack_sendmap* rack_alloc (struct tcp_rack*) ; 
 int /*<<< orphan*/  rack_alloc_limited_conns ; 
 int /*<<< orphan*/  rack_split_limited ; 
 scalar_t__ rack_tcp_map_split_limit ; 

__attribute__((used)) static struct rack_sendmap *
rack_alloc_limit(struct tcp_rack *rack, uint8_t limit_type)
{
	struct rack_sendmap *rsm;

	if (limit_type) {
		/* currently there is only one limit type */
		if (rack_tcp_map_split_limit > 0 &&
		    (rack->do_detection == 0) &&
		    rack->r_ctl.rc_num_split_allocs >= rack_tcp_map_split_limit) {
			counter_u64_add(rack_split_limited, 1);
			if (!rack->alloc_limit_reported) {
				rack->alloc_limit_reported = 1;
				counter_u64_add(rack_alloc_limited_conns, 1);
			}
			return (NULL);
		}
	}

	/* allocate and mark in the limit type, if set */
	rsm = rack_alloc(rack);
	if (rsm != NULL && limit_type) {
		rsm->r_limit_type = limit_type;
		rack->r_ctl.rc_num_split_allocs++;
	}
	return (rsm);
}