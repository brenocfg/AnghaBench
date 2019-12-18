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
struct rulehead {int dummy; } ;
struct rule {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PORTACL ; 
 struct rule* TAILQ_FIRST (struct rulehead*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct rulehead*,struct rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_entries ; 

__attribute__((used)) static void
toast_rules(struct rulehead *head)
{
	struct rule *rule;

	while ((rule = TAILQ_FIRST(head)) != NULL) {
		TAILQ_REMOVE(head, rule, r_entries);
		free(rule, M_PORTACL);
	}
}