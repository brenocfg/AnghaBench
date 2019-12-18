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
typedef  int /*<<< orphan*/  camdd_argmask ;

/* Variables and functions */
 int /*<<< orphan*/  CAMDD_ARG_BUS ; 
 int /*<<< orphan*/  CAMDD_ARG_LUN ; 
 int /*<<< orphan*/  CAMDD_ARG_TARGET ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ strtok (char*,char*) ; 
 int strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_btl(char *tstr, int *bus, int *target, int *lun, camdd_argmask *arglst)
{
	char *tmpstr;
	int convs = 0;

	while (isspace(*tstr) && (*tstr != '\0'))
		tstr++;

	tmpstr = (char *)strtok(tstr, ":");
	if ((tmpstr != NULL) && (*tmpstr != '\0')) {
		*bus = strtol(tmpstr, NULL, 0);
		*arglst |= CAMDD_ARG_BUS;
		convs++;
		tmpstr = (char *)strtok(NULL, ":");
		if ((tmpstr != NULL) && (*tmpstr != '\0')) {
			*target = strtol(tmpstr, NULL, 0);
			*arglst |= CAMDD_ARG_TARGET;
			convs++;
			tmpstr = (char *)strtok(NULL, ":");
			if ((tmpstr != NULL) && (*tmpstr != '\0')) {
				*lun = strtol(tmpstr, NULL, 0);
				*arglst |= CAMDD_ARG_LUN;
				convs++;
			}
		}
	}

	return convs;
}