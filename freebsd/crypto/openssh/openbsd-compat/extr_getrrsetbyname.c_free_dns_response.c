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
struct dns_response {int /*<<< orphan*/  additional; int /*<<< orphan*/  authority; int /*<<< orphan*/  answer; int /*<<< orphan*/  query; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct dns_response*) ; 
 int /*<<< orphan*/  free_dns_query (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dns_rr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_dns_response(struct dns_response *p)
{
	if (p == NULL)
		return;

	free_dns_query(p->query);
	free_dns_rr(p->answer);
	free_dns_rr(p->authority);
	free_dns_rr(p->additional);
	free(p);
}