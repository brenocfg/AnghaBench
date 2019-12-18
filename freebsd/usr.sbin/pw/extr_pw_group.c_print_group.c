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
struct group {char* gr_name; long* gr_mem; scalar_t__ gr_gid; } ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* gr_make (struct group*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
print_group(struct group * grp, bool pretty)
{
	char *buf = NULL;
	int i;

	if (pretty) {
		printf("Group Name: %-15s   #%lu\n"
		       "   Members: ",
		       grp->gr_name, (long) grp->gr_gid);
		if (grp->gr_mem != NULL) {
			for (i = 0; grp->gr_mem[i]; i++)
				printf("%s%s", i ? "," : "", grp->gr_mem[i]);
		}
		fputs("\n\n", stdout);
		return (EXIT_SUCCESS);
	}

	buf = gr_make(grp);
	printf("%s\n", buf);
	free(buf);
	return (EXIT_SUCCESS);
}