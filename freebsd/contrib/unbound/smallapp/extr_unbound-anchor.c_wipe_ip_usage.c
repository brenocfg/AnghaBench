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
struct ip_list {struct ip_list* next; scalar_t__ used; } ;

/* Variables and functions */

__attribute__((used)) static void
wipe_ip_usage(struct ip_list* p)
{
	while(p) {
		p->used = 0;
		p = p->next;
	}
}