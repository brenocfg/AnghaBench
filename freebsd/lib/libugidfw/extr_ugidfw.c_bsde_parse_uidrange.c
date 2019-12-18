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
typedef  unsigned long uid_t ;
struct passwd {unsigned long pw_uid; } ;

/* Variables and functions */
 struct passwd* getpwnam (char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 char* strsep (char**,char*) ; 
 unsigned long strtoul (char*,char**,int) ; 

__attribute__((used)) static int
bsde_parse_uidrange(char *spec, uid_t *min, uid_t *max,
    size_t buflen, char *errstr){
	struct passwd *pwd;
	uid_t uid1, uid2;
	char *spec1, *spec2, *endp;
	unsigned long value;

	spec2 = spec;
	spec1 = strsep(&spec2, ":");

	pwd = getpwnam(spec1);
	if (pwd != NULL)
		uid1 = pwd->pw_uid;
	else {
		value = strtoul(spec1, &endp, 10);
		if (*endp != '\0') {
			snprintf(errstr, buflen, "invalid uid: '%s'", spec1);
			return (-1);
		}
		uid1 = value;
	}

	if (spec2 == NULL) {
		*max = *min = uid1;
		return (0);
	}

	pwd = getpwnam(spec2);
	if (pwd != NULL)
		uid2 = pwd->pw_uid;
	else {
		value = strtoul(spec2, &endp, 10);
		if (*endp != '\0') {
			snprintf(errstr, buflen, "invalid uid: '%s'", spec2);
			return (-1);
		}
		uid2 = value;
	}

	*min = uid1;
	*max = uid2;

	return (0);
}