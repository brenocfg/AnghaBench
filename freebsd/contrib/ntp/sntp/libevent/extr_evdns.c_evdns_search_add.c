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

/* Variables and functions */
 int /*<<< orphan*/  current_base ; 
 int /*<<< orphan*/  evdns_base_search_add (int /*<<< orphan*/ ,char const*) ; 

void
evdns_search_add(const char *domain) {
	evdns_base_search_add(current_base, domain);
}