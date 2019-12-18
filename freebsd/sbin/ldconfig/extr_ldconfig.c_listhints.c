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
struct shlib_list {char* name; int major; int minor; char* path; struct shlib_list* next; } ;

/* Variables and functions */
 char* dir_list ; 
 char* hints_file ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct shlib_list* shlib_head ; 

__attribute__((used)) static void
listhints(void)
{
	struct shlib_list	*shp;
	int			i;

	printf("%s:\n", hints_file);
	printf("\tsearch directories: %s\n", dir_list);

	for (i = 0, shp = shlib_head; shp; i++, shp = shp->next)
		printf("\t%d:-l%s.%d.%d => %s\n",
			i, shp->name, shp->major, shp->minor, shp->path);

	return;
}