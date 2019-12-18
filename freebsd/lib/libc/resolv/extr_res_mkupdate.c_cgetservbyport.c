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
struct valuelist {int /*<<< orphan*/  proto; scalar_t__ port; int /*<<< orphan*/  name; struct valuelist* next; struct valuelist* prev; } ;
struct servent {int /*<<< orphan*/  s_proto; int /*<<< orphan*/  s_port; int /*<<< orphan*/  s_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (scalar_t__) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 struct valuelist* servicelist ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct servent *
cgetservbyport(u_int16_t port, const char *proto) {	/*%< Host byte order. */
	struct valuelist **list = &servicelist;
	struct valuelist *lp = *list;
	static struct servent serv;

	port = ntohs(port);
	for (; lp != NULL; lp = lp->next) {
		if (port != (u_int16_t)lp->port)	/*%< Host byte order. */
			continue;
		if (strcasecmp(lp->proto, proto) == 0) {
			if (lp != *list) {
				lp->prev->next = lp->next;
				if (lp->next)
					lp->next->prev = lp->prev;
				(*list)->prev = lp;
				lp->next = *list;
				*list = lp;
			}
			serv.s_name = lp->name;
			serv.s_port = htons((u_int16_t)lp->port);
			serv.s_proto = lp->proto;
			return (&serv);
		}
	}
	return (0);
}