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
typedef  int /*<<< orphan*/  uint32_t ;
struct camcontrol_opts {char* subopt; int /*<<< orphan*/  argnum; int /*<<< orphan*/  cmdnum; int /*<<< orphan*/ * optname; } ;
typedef  int /*<<< orphan*/  camcontrol_optret ;
typedef  int /*<<< orphan*/  cam_argmask ;

/* Variables and functions */
 int /*<<< orphan*/  CC_OR_AMBIGUOUS ; 
 int /*<<< orphan*/  CC_OR_FOUND ; 
 int /*<<< orphan*/  CC_OR_NOT_FOUND ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

camcontrol_optret
getoption(struct camcontrol_opts *table, char *arg, uint32_t *cmdnum,
	  cam_argmask *argnum, const char **subopt)
{
	struct camcontrol_opts *opts;
	int num_matches = 0;

	for (opts = table; (opts != NULL) && (opts->optname != NULL);
	     opts++) {
		if (strncmp(opts->optname, arg, strlen(arg)) == 0) {
			*cmdnum = opts->cmdnum;
			*argnum = opts->argnum;
			*subopt = opts->subopt;
			if (++num_matches > 1)
				return (CC_OR_AMBIGUOUS);
		}
	}

	if (num_matches > 0)
		return (CC_OR_FOUND);
	else
		return (CC_OR_NOT_FOUND);
}