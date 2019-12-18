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
struct group {unsigned long gr_gid; } ;
typedef  unsigned long gid_t ;

/* Variables and functions */
 struct group* getgrnam (char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 char* strsep (char**,char*) ; 
 unsigned long strtoul (char*,char**,int) ; 

__attribute__((used)) static int
bsde_parse_gidrange(char *spec, gid_t *min, gid_t *max,
    size_t buflen, char *errstr){
	struct group *grp;
	gid_t gid1, gid2;
	char *spec1, *spec2, *endp;
	unsigned long value;

	spec2 = spec;
	spec1 = strsep(&spec2, ":");

	grp = getgrnam(spec1);
	if (grp != NULL)
		gid1 = grp->gr_gid;
	else {
		value = strtoul(spec1, &endp, 10);
		if (*endp != '\0') {
			snprintf(errstr, buflen, "invalid gid: '%s'", spec1);
			return (-1);
		}
		gid1 = value;
	}

	if (spec2 == NULL) {
		*max = *min = gid1;
		return (0);
	}

	grp = getgrnam(spec2);
	if (grp != NULL)
		gid2 = grp->gr_gid;
	else {
		value = strtoul(spec2, &endp, 10);
		if (*endp != '\0') {
			snprintf(errstr, buflen, "invalid gid: '%s'", spec2);
			return (-1);
		}
		gid2 = value;
	}

	*min = gid1;
	*max = gid2;

	return (0);
}