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
struct valuelist {int port; struct valuelist* next; struct valuelist* prev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int sscanf (char const*,char*,int*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
findservice(const char *s, struct valuelist **list) {
	struct valuelist *lp = *list;
	int n;

	for (; lp != NULL; lp = lp->next)
		if (strcasecmp(lp->name, s) == 0) {
			if (lp != *list) {
				lp->prev->next = lp->next;
				if (lp->next)
					lp->next->prev = lp->prev;
				(*list)->prev = lp;
				lp->next = *list;
				*list = lp;
			}
			return (lp->port);	/*%< host byte order */
		}
	if (sscanf(s, "%d", &n) != 1 || n <= 0)
		n = -1;
	return (n);
}