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
struct grouphead {struct group* g_list; struct grouphead* g_link; void* g_name; } ;
struct group {struct group* ge_link; void* ge_name; } ;

/* Variables and functions */
 int HSHSIZE ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 struct grouphead* findgroup (char*) ; 
 struct grouphead** groups ; 
 int hash (char*) ; 
 int /*<<< orphan*/  printgroup (char*) ; 
 scalar_t__ salloc (int) ; 
 int /*<<< orphan*/  sort (char**) ; 
 void* vcopy (char*) ; 

int
group(void *v)
{
	char **argv = v;
	struct grouphead *gh;
	struct group *gp;
	char **ap, *gname, **p;
	int h, s;

	if (*argv == NULL) {
		for (h = 0, s = 1; h < HSHSIZE; h++)
			for (gh = groups[h]; gh != NULL; gh = gh->g_link)
				s++;
		ap = (char **)salloc(s * sizeof(*ap));
		for (h = 0, p = ap; h < HSHSIZE; h++)
			for (gh = groups[h]; gh != NULL; gh = gh->g_link)
				*p++ = gh->g_name;
		*p = NULL;
		sort(ap);
		for (p = ap; *p != NULL; p++)
			printgroup(*p);
		return (0);
	}
	if (argv[1] == NULL) {
		printgroup(*argv);
		return (0);
	}
	gname = *argv;
	h = hash(gname);
	if ((gh = findgroup(gname)) == NULL) {
		if ((gh = calloc(1, sizeof(*gh))) == NULL)
			err(1, "Out of memory");
		gh->g_name = vcopy(gname);
		gh->g_list = NULL;
		gh->g_link = groups[h];
		groups[h] = gh;
	}

	/*
	 * Insert names from the command list into the group.
	 * Who cares if there are duplicates?  They get tossed
	 * later anyway.
	 */

	for (ap = argv+1; *ap != NULL; ap++) {
		if ((gp = calloc(1, sizeof(*gp))) == NULL)
			err(1, "Out of memory");
		gp->ge_name = vcopy(*ap);
		gp->ge_link = gh->g_list;
		gh->g_list = gp;
	}
	return (0);
}