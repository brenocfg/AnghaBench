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
struct env_lst {char* var; char* value; scalar_t__ export; struct env_lst* next; } ;
struct TYPE_2__ {struct env_lst* next; } ;

/* Variables and functions */
 TYPE_1__ envlisthead ; 
 int /*<<< orphan*/  printf (char*,char,char*,char*) ; 

void
env_list(void)
{
	struct env_lst *ep;

	for (ep = envlisthead.next; ep; ep = ep->next) {
		printf("%c %-20s %s\r\n", ep->export ? '*' : ' ',
					ep->var, ep->value);
	}
}