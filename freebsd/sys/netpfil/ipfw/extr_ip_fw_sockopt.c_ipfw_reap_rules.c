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
struct ip_fw {struct ip_fw* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipfw_free_rule (struct ip_fw*) ; 

void
ipfw_reap_rules(struct ip_fw *head)
{
	struct ip_fw *rule;

	while ((rule = head) != NULL) {
		head = head->next;
		ipfw_free_rule(rule);
	}
}