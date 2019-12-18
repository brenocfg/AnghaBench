#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cfparam {int /*<<< orphan*/  val; } ;
struct TYPE_2__ {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfstrings ; 
 int strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int
int_param(const struct cfparam *p, int *ip)
{
	if (p == NULL || TAILQ_EMPTY(&p->val))
		return 0;
	*ip = strtol(TAILQ_LAST(&p->val, cfstrings)->s, NULL, 10);
	return 1;
}