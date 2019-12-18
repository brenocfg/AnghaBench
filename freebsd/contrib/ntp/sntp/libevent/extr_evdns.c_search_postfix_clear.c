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
struct evdns_base {int /*<<< orphan*/  global_search_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  search_state_decref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_state_new () ; 

__attribute__((used)) static void
search_postfix_clear(struct evdns_base *base) {
	search_state_decref(base->global_search_state);

	base->global_search_state = search_state_new();
}