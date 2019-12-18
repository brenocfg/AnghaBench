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
struct config_view {struct config_view* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_delview (struct config_view*) ; 

void
config_delviews(struct config_view* p)
{
	struct config_view* np;
	while(p) {
		np = p->next;
		config_delview(p);
		p = np;
	}
}