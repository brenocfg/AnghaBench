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
typedef  scalar_t__ u_int16_t ;
struct dns_rr {scalar_t__ class; scalar_t__ type; struct dns_rr* next; } ;

/* Variables and functions */

__attribute__((used)) static int
count_dns_rr(struct dns_rr *p, u_int16_t class, u_int16_t type)
{
	int n = 0;

	while(p) {
		if (p->class == class && p->type == type)
			n++;
		p = p->next;
	}

	return (n);
}