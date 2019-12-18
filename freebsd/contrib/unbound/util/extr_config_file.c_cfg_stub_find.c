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
struct config_stub {struct config_stub* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct config_stub* cfg_stub_find(struct config_stub*** pp, const char* nm)
{
	struct config_stub* p = *(*pp);
	while(p) {
		if(strcmp(p->name, nm) == 0)
			return p;
		(*pp) = &p->next;
		p = p->next;
	}
	return NULL;
}