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
struct ifaddrs {struct ifaddrs* ifa_next; TYPE_1__* ifa_addr; int /*<<< orphan*/  ifa_name; } ;
struct ifa_queue {int dummy; } ;
struct ifa_order_elt {unsigned int* af_orders; struct ifaddrs* ifa; int /*<<< orphan*/  if_order; } ;
struct TYPE_2__ {unsigned int sa_family; } ;

/* Variables and functions */
 unsigned int ORDERS_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct ifa_queue*,struct ifa_order_elt*,int /*<<< orphan*/ ) ; 
 struct ifa_order_elt* calloc (int,int) ; 
 int /*<<< orphan*/  link ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
calcorders(struct ifaddrs *ifa, struct ifa_queue *q)
{
	struct ifaddrs *prev;
	struct ifa_order_elt *cur;
	unsigned int ord, af, ifa_ord;

	prev = NULL;
	cur = NULL;
	ord = 0;
	ifa_ord = 0;

	while (ifa != NULL) {
		if (prev == NULL ||
		    strcmp(ifa->ifa_name, prev->ifa_name) != 0) {
			cur = calloc(1, sizeof(*cur));

			if (cur == NULL)
				return (-1);

			TAILQ_INSERT_TAIL(q, cur, link);
			cur->if_order = ifa_ord ++;
			cur->ifa = ifa;
			ord = 0;
		}

		if (ifa->ifa_addr) {
			af = ifa->ifa_addr->sa_family;

			if (af < ORDERS_SIZE(cur->af_orders) &&
			    cur->af_orders[af] == 0)
				cur->af_orders[af] = ++ord;
		}
		prev = ifa;
		ifa = ifa->ifa_next;
	}

	return (0);
}