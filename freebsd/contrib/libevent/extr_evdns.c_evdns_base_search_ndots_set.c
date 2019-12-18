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
struct evdns_base {TYPE_1__* global_search_state; } ;
struct TYPE_2__ {int ndots; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 TYPE_1__* search_state_new () ; 

void
evdns_base_search_ndots_set(struct evdns_base *base, const int ndots) {
	EVDNS_LOCK(base);
	if (!base->global_search_state) base->global_search_state = search_state_new();
	if (base->global_search_state)
		base->global_search_state->ndots = ndots;
	EVDNS_UNLOCK(base);
}