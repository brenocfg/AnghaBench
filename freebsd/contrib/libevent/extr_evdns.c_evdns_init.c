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
struct evdns_base {int dummy; } ;

/* Variables and functions */
 struct evdns_base* current_base ; 
 struct evdns_base* evdns_base_new (int /*<<< orphan*/ *,int) ; 

int
evdns_init(void)
{
	struct evdns_base *base = evdns_base_new(NULL, 1);
	if (base) {
		current_base = base;
		return 0;
	} else {
		return -1;
	}
}