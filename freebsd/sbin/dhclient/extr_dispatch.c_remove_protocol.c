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
struct protocol {struct protocol* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct protocol*) ; 
 struct protocol* protocols ; 

void
remove_protocol(struct protocol *proto)
{
	struct protocol *p, *next;

	for (p = protocols; p; p = next) {
		next = p->next;
		if (p == proto) {
			protocols = p->next;
			free(p);
		}
	}
}