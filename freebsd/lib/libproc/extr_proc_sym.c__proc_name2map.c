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
struct proc_handle {size_t nmappings; size_t exec_map; struct map_info* mappings; } ;
struct TYPE_2__ {int /*<<< orphan*/  pr_vaddr; int /*<<< orphan*/  pr_mapname; } ;
struct map_info {TYPE_1__ map; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int MAXPATHLEN ; 
 struct map_info* _proc_addr2map (struct proc_handle*,int /*<<< orphan*/ ) ; 
 char* basename (char*) ; 
 int /*<<< orphan*/ * proc_rdagent (struct proc_handle*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 

__attribute__((used)) static struct map_info *
_proc_name2map(struct proc_handle *p, const char *name)
{
	char path[MAXPATHLEN], *base;
	struct map_info *mapping;
	size_t i, len;

	if ((len = strlen(name)) == 0)
		return (NULL);
	if (p->nmappings == 0)
		if (proc_rdagent(p) == NULL)
			return (NULL);
	for (i = 0; i < p->nmappings; i++) {
		mapping = &p->mappings[i];
		(void)strlcpy(path, mapping->map.pr_mapname, sizeof(path));
		base = basename(path);
		if (strcmp(base, name) == 0)
			return (mapping);
	}
	/* If we didn't find a match, try matching prefixes of the basename. */
	for (i = 0; i < p->nmappings; i++) {
		mapping = &p->mappings[i];
		strlcpy(path, mapping->map.pr_mapname, sizeof(path));
		base = basename(path);
		if (strncmp(base, name, len) == 0)
			return (mapping);
	}
	if (strcmp(name, "a.out") == 0)
		return (_proc_addr2map(p,
		    p->mappings[p->exec_map].map.pr_vaddr));
	return (NULL);
}