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
struct pfctl {unsigned int* limit; int* limit_set; int opts; } ;
struct TYPE_2__ {size_t index; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int PF_OPT_VERBOSE ; 
 TYPE_1__* pf_limits ; 
 int /*<<< orphan*/  printf (char*,char const*,unsigned int) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
pfctl_set_limit(struct pfctl *pf, const char *opt, unsigned int limit)
{
	int i;


	for (i = 0; pf_limits[i].name; i++) {
		if (strcasecmp(opt, pf_limits[i].name) == 0) {
			pf->limit[pf_limits[i].index] = limit;
			pf->limit_set[pf_limits[i].index] = 1;
			break;
		}
	}
	if (pf_limits[i].name == NULL) {
		warnx("Bad pool name.");
		return (1);
	}

	if (pf->opts & PF_OPT_VERBOSE)
		printf("set limit %s %d\n", opt, limit);

	return (0);
}