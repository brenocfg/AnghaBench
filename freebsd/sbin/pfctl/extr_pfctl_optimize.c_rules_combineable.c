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
struct pf_rule {int dummy; } ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  COMBINED ; 
 int /*<<< orphan*/  comparable_rule (struct pf_rule*,struct pf_rule*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct pf_rule*,struct pf_rule*,int) ; 

int
rules_combineable(struct pf_rule *p1, struct pf_rule *p2)
{
	struct pf_rule a, b;

	comparable_rule(&a, p1, COMBINED);
	comparable_rule(&b, p2, COMBINED);
	return (memcmp(&a, &b, sizeof(a)) == 0);
}