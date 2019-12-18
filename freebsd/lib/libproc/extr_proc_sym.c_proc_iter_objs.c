#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct proc_handle {size_t nmappings; TYPE_1__* mappings; } ;
typedef  int (* proc_map_f ) (void*,TYPE_2__*,char*) ;
struct TYPE_7__ {char* pr_mapname; } ;
typedef  TYPE_2__ prmap_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  last ;
struct TYPE_6__ {TYPE_2__ map; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * proc_rdagent (struct proc_handle*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int stub1 (void*,TYPE_2__*,char*) ; 

int
proc_iter_objs(struct proc_handle *p, proc_map_f *func, void *cd)
{
	char last[MAXPATHLEN], path[MAXPATHLEN], *base;
	prmap_t *map;
	size_t i;
	int error;

	if (p->nmappings == 0)
		if (proc_rdagent(p) == NULL)
			return (-1);

	error = 0;
	memset(last, 0, sizeof(last));
	for (i = 0; i < p->nmappings; i++) {
		map = &p->mappings[i].map;
		strlcpy(path, map->pr_mapname, sizeof(path));
		base = basename(path);
		/*
		 * We shouldn't call the callback twice with the same object.
		 * To do that we are assuming the fact that if there are
		 * repeated object names (i.e. different mappings for the
		 * same object) they occur next to each other.
		 */
		if (strcmp(base, last) == 0)
			continue;
		if ((error = (*func)(cd, map, base)) != 0)
			break;
		strlcpy(last, path, sizeof(last));
	}
	return (error);
}