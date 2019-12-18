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
struct TYPE_2__ {scalar_t__ rc_num_maps_alloced; } ;
struct tcp_rack {scalar_t__ do_detection; int alloc_limit_reported; TYPE_1__ r_ctl; } ;
struct rack_sendmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 struct rack_sendmap* rack_alloc (struct tcp_rack*) ; 
 int /*<<< orphan*/  rack_alloc_limited_conns ; 
 scalar_t__ rack_tcp_map_entries_limit ; 
 int /*<<< orphan*/  rack_to_alloc_limited ; 

__attribute__((used)) static struct rack_sendmap *
rack_alloc_full_limit(struct tcp_rack *rack)
{
	if ((rack_tcp_map_entries_limit > 0) &&
	    (rack->do_detection == 0) &&
	    (rack->r_ctl.rc_num_maps_alloced >= rack_tcp_map_entries_limit)) {
		counter_u64_add(rack_to_alloc_limited, 1);
		if (!rack->alloc_limit_reported) {
			rack->alloc_limit_reported = 1;
			counter_u64_add(rack_alloc_limited_conns, 1);
		}
		return (NULL);
	}
	return (rack_alloc(rack));
}