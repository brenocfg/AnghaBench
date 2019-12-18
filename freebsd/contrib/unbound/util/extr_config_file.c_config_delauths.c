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
struct config_auth {struct config_auth* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_delauth (struct config_auth*) ; 

void
config_delauths(struct config_auth* p)
{
	struct config_auth* np;
	while(p) {
		np = p->next;
		config_delauth(p);
		p = np;
	}
}