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
struct expression {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int valid_pmc_cnt ; 
 int /*<<< orphan*/ * valid_pmcs ; 

__attribute__((used)) static void
pmc_name_set(struct expression *at)
{
	int i, idx, fnd;

	if (at->name[0] == '%') {
		/* Special number after $ gives index */
		idx = strtol(&at->name[1], NULL, 0);
		if (idx >= valid_pmc_cnt) {
			printf("Unknown PMC %s -- largest we have is $%d -- can't run your expression\n",
			       at->name, valid_pmc_cnt);
			exit(-1);
		}
		strcpy(at->name, valid_pmcs[idx]);
	} else {
		for(i=0, fnd=0; i<valid_pmc_cnt; i++) {
			if (strcmp(valid_pmcs[i], at->name) == 0) {
				fnd = 1;
				break;
			}
		}
		if (!fnd) {
			printf("PMC %s does not exist on this machine -- can't run your expression\n",
			       at->name);
			exit(-1);
		}
	}
}