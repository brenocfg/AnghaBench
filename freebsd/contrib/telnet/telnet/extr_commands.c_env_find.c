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
struct env_lst {int /*<<< orphan*/  var; struct env_lst* next; } ;
struct TYPE_2__ {struct env_lst* next; } ;

/* Variables and functions */
 TYPE_1__ envlisthead ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,unsigned char const*) ; 

__attribute__((used)) static struct env_lst *
env_find(const unsigned char *var)
{
	struct env_lst *ep;

	for (ep = envlisthead.next; ep; ep = ep->next) {
		if (strcmp(ep->var, var) == 0)
			return(ep);
	}
	return(NULL);
}