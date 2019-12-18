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
typedef  int /*<<< orphan*/  target_id_t ;
typedef  int /*<<< orphan*/  path_id_t ;
typedef  int /*<<< orphan*/  lun_id_t ;

/* Variables and functions */
 int CAM_ARG_BUS ; 
 int CAM_ARG_LUN ; 
 int /*<<< orphan*/  CAM_BUS_WILDCARD ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int arglist ; 
 scalar_t__ isspace (char) ; 
 size_t optind ; 
 int parse_btl (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int rescan_or_reset_bus (int /*<<< orphan*/ ,int) ; 
 int scanlun_or_reset_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char const*,char*) ; 

__attribute__((used)) static int
dorescan_or_reset(int argc, char **argv, int rescan)
{
	static const char must[] =
	    "you must specify \"all\", a bus, a bus:target:lun or periph to %s";
	int rv, error = 0;
	path_id_t bus = CAM_BUS_WILDCARD;
	target_id_t target = CAM_TARGET_WILDCARD;
	lun_id_t lun = CAM_LUN_WILDCARD;
	char *tstr;

	if (argc < 3) {
		warnx(must, rescan? "rescan" : "reset");
		return (1);
	}

	tstr = argv[optind];
	while (isspace(*tstr) && (*tstr != '\0'))
		tstr++;
	if (strncasecmp(tstr, "all", strlen("all")) == 0)
		arglist |= CAM_ARG_BUS;
	else {
		rv = parse_btl(argv[optind], &bus, &target, &lun, &arglist);
		if (rv != 1 && rv != 3) {
			warnx(must, rescan ? "rescan" : "reset");
			return (1);
		}
	}

	if (arglist & CAM_ARG_LUN)
		error = scanlun_or_reset_dev(bus, target, lun, rescan);
	else
		error = rescan_or_reset_bus(bus, rescan);

	return (error);
}