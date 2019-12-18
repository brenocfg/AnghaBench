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
struct config_stub {struct config_stub* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_delstub (struct config_stub*) ; 

void
config_delstubs(struct config_stub* p)
{
	struct config_stub* np;
	while(p) {
		np = p->next;
		config_delstub(p);
		p = np;
	}
}