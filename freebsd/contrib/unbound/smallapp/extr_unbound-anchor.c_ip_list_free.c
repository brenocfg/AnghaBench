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
struct ip_list {struct ip_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ip_list*) ; 

__attribute__((used)) static void
ip_list_free(struct ip_list* p)
{
	struct ip_list* np;
	while(p) {
		np = p->next;
		free(p);
		p = np;
	}
}