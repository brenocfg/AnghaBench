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
struct dns_query {struct dns_query* next; struct dns_query* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct dns_query*) ; 

__attribute__((used)) static void
free_dns_query(struct dns_query *p)
{
	if (p == NULL)
		return;

	if (p->name)
		free(p->name);
	free_dns_query(p->next);
	free(p);
}