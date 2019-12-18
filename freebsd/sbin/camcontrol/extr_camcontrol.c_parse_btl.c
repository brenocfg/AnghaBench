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
typedef  void* target_id_t ;
typedef  void* path_id_t ;
typedef  int /*<<< orphan*/  lun_id_t ;
typedef  int /*<<< orphan*/  cam_argmask ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_ARG_BUS ; 
 int /*<<< orphan*/  CAM_ARG_LUN ; 
 int /*<<< orphan*/  CAM_ARG_TARGET ; 
 void* CAM_BUS_WILDCARD ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 void* CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  arglist ; 
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ isspace (char) ; 
 int parse_btl_name (char*,void**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 void* strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoll (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_btl(char *tstr, path_id_t *bus, target_id_t *target, lun_id_t *lun,
    cam_argmask *arglst)
{
	char *tmpstr, *end;
	int convs = 0;

	*bus = CAM_BUS_WILDCARD;
	*target = CAM_TARGET_WILDCARD;
	*lun = CAM_LUN_WILDCARD;

	while (isspace(*tstr) && (*tstr != '\0'))
		tstr++;

	if (strncasecmp(tstr, "all", strlen("all")) == 0) {
		arglist |= CAM_ARG_BUS;
		return (1);
	}

	if (!isdigit(*tstr))
		return (parse_btl_name(tstr, bus, target, lun, arglst));

	tmpstr = strsep(&tstr, ":");
	if ((tmpstr != NULL) && (*tmpstr != '\0')) {
		*bus = strtol(tmpstr, &end, 0);
		if (*end != '\0')
			return (0);
		*arglst |= CAM_ARG_BUS;
		convs++;
		tmpstr = strsep(&tstr, ":");
		if ((tmpstr != NULL) && (*tmpstr != '\0')) {
			*target = strtol(tmpstr, &end, 0);
			if (*end != '\0')
				return (0);
			*arglst |= CAM_ARG_TARGET;
			convs++;
			tmpstr = strsep(&tstr, ":");
			if ((tmpstr != NULL) && (*tmpstr != '\0')) {
				*lun = strtoll(tmpstr, &end, 0);
				if (*end != '\0')
					return (0);
				*arglst |= CAM_ARG_LUN;
				convs++;
			}
		}
	}

	return convs;
}