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
struct auth_master {int /*<<< orphan*/  host; struct auth_master* next; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct auth_master*
find_master_by_host(struct auth_master* list, char* host)
{
	struct auth_master* p;
	for(p=list; p; p=p->next) {
		if(strcmp(p->host, host) == 0)
			return p;
	}
	return NULL;
}