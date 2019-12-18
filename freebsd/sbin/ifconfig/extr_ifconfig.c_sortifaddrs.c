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
struct ifaddrs {struct ifaddrs* ifa_next; } ;
struct ifa_queue {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct ifaddrs *
sortifaddrs(struct ifaddrs *list,
    int (*compare)(struct ifaddrs *, struct ifaddrs *, struct ifa_queue *),
    struct ifa_queue *q)
{
	struct ifaddrs *right, *temp, *last, *result, *next, *tail;
	
	right = list;
	temp = list;
	last = list;
	result = NULL;
	next = NULL;
	tail = NULL;

	if (!list || !list->ifa_next)
		return (list);

	while (temp && temp->ifa_next) {
		last = right;
		right = right->ifa_next;
		temp = temp->ifa_next->ifa_next;
	}

	last->ifa_next = NULL;

	list = sortifaddrs(list, compare, q);
	right = sortifaddrs(right, compare, q);

	while (list || right) {

		if (!right) {
			next = list;
			list = list->ifa_next;
		} else if (!list) {
			next = right;
			right = right->ifa_next;
		} else if (compare(list, right, q) <= 0) {
			next = list;
			list = list->ifa_next;
		} else {
			next = right;
			right = right->ifa_next;
		}

		if (!result)
			result = next;
		else
			tail->ifa_next = next;

		tail = next;
	}

	return (result);
}