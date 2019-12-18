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
struct child {scalar_t__ pid; struct child* link; scalar_t__ free; scalar_t__ done; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 struct child* child ; 
 struct child* child_freelist ; 
 int /*<<< orphan*/  err (int,char*) ; 
 struct child* malloc (int) ; 

__attribute__((used)) static struct child *
findchild(pid_t pid, int dont_alloc)
{
	struct child **cpp;

	for (cpp = &child; *cpp != NULL && (*cpp)->pid != pid;
	    cpp = &(*cpp)->link)
			;
	if (*cpp == NULL) {
		if (dont_alloc)
			return(NULL);
		if (child_freelist) {
			*cpp = child_freelist;
			child_freelist = (*cpp)->link;
		} else {
			*cpp = malloc(sizeof(struct child));
			if (*cpp == NULL)
				err(1, "malloc");
		}
		(*cpp)->pid = pid;
		(*cpp)->done = (*cpp)->free = 0;
		(*cpp)->link = NULL;
	}
	return (*cpp);
}