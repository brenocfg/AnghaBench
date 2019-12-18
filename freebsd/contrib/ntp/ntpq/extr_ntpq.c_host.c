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
struct parse {int nargs; TYPE_1__* argval; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ai_fam_default ; 
 int /*<<< orphan*/  ai_fam_templ ; 
 char* currenthost ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ havehost ; 
 scalar_t__ openhost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
host(
	struct parse *pcmd,
	FILE *fp
	)
{
	int i;

	if (pcmd->nargs == 0) {
		if (havehost)
			(void) fprintf(fp, "current host is %s\n",
					   currenthost);
		else
			(void) fprintf(fp, "no current host\n");
		return;
	}

	i = 0;
	ai_fam_templ = ai_fam_default;
	if (pcmd->nargs == 2) {
		if (!strcmp("-4", pcmd->argval[i].string))
			ai_fam_templ = AF_INET;
		else if (!strcmp("-6", pcmd->argval[i].string))
			ai_fam_templ = AF_INET6;
		else
			goto no_change;
		i = 1;
	}
	if (openhost(pcmd->argval[i].string, ai_fam_templ)) {
		fprintf(fp, "current host set to %s\n", currenthost);
	} else {
    no_change:
		if (havehost)
			fprintf(fp, "current host remains %s\n",
				currenthost);
		else
			fprintf(fp, "still no current host\n");
	}
}