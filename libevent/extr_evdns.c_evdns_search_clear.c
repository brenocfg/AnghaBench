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
 int /*<<< orphan*/  evdns_base_search_clear (int /*<<< orphan*/ ) ; 

void
evdns_search_clear(void) {
	evdns_base_search_clear(current_base);
}