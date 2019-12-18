#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* dinfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  generation; int /*<<< orphan*/  numdevs; } ;

/* Variables and functions */
 scalar_t__ BOOT ; 
 int /*<<< orphan*/  MAXDRIVES ; 
 scalar_t__ RUN ; 
 scalar_t__ TIME ; 
 int /*<<< orphan*/  copyinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cur_dev ; 
 int /*<<< orphan*/  devstat_errbuf ; 
 int devstat_getdevs (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int dscmd (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generation ; 
 int /*<<< orphan*/  getinfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  labelkre () ; 
 int /*<<< orphan*/  num_devices ; 
 scalar_t__ prefix (char const*,char*) ; 
 TYPE_2__ run_dev ; 
 int /*<<< orphan*/  s1 ; 
 int /*<<< orphan*/  s2 ; 
 scalar_t__ state ; 
 int /*<<< orphan*/  z ; 

int
cmdkre(const char *cmd, const char *args)
{
	int retval;

	if (prefix(cmd, "run")) {
		retval = 1;
		copyinfo(&s2, &s1);
		switch (devstat_getdevs(NULL, &run_dev)) {
		case -1:
			errx(1, "%s", devstat_errbuf);
			break;
		case 1:
			num_devices = run_dev.dinfo->numdevs;
			generation = run_dev.dinfo->generation;
			retval = dscmd("refresh", NULL, MAXDRIVES, &cur_dev);
			if (retval == 2)
				labelkre();
			break;
		default:
			break;
		}
		state = RUN;
		return (retval);
	}
	if (prefix(cmd, "boot")) {
		state = BOOT;
		copyinfo(&z, &s1);
		return (1);
	}
	if (prefix(cmd, "time")) {
		state = TIME;
		return (1);
	}
	if (prefix(cmd, "zero")) {
		retval = 1;
		if (state == RUN) {
			getinfo(&s1);
			switch (devstat_getdevs(NULL, &run_dev)) {
			case -1:
				errx(1, "%s", devstat_errbuf);
				break;
			case 1:
				num_devices = run_dev.dinfo->numdevs;
				generation = run_dev.dinfo->generation;
				retval = dscmd("refresh",NULL, MAXDRIVES, &cur_dev);
				if (retval == 2)
					labelkre();
				break;
			default:
				break;
			}
		}
		return (retval);
	}
	retval = dscmd(cmd, args, MAXDRIVES, &cur_dev);

	if (retval == 2)
		labelkre();

	return(retval);
}