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
struct rcfile {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int rc_getstringptr (struct rcfile*,char const*,char const*,char**) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,char const*,size_t) ; 

int
rc_getstring(struct rcfile *rcp, const char *section, const char *key,
	size_t maxlen, char *dest)
{
	char *value;
	int error;

	error = rc_getstringptr(rcp, section, key, &value);
	if (error)
		return error;
	if (strlen(value) >= maxlen) {
		warnx("line too long for key '%s' in section '%s', max = %zd\n", key, section, maxlen);
		return EINVAL;
	}
	strcpy(dest, value);
	return 0;
}