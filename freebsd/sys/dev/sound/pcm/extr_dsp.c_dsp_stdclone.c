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

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ bcmp (char*,char*,size_t) ; 
 int dsp_cmax ; 
 int dsp_umax ; 
 scalar_t__ isdigit (char) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
dsp_stdclone(char *name, char *namep, char *sep, int use_sep, int *u, int *c)
{
	size_t len;

	len = strlen(namep);

	if (bcmp(name, namep, len) != 0)
		return (ENODEV);

	name += len;

	if (isdigit(*name) == 0)
		return (ENODEV);

	len = strlen(sep);

	if (*name == '0' && !(name[1] == '\0' || bcmp(name + 1, sep, len) == 0))
		return (ENODEV);

	for (*u = 0; isdigit(*name) != 0; name++) {
		*u *= 10;
		*u += *name - '0';
		if (*u > dsp_umax)
			return (ENODEV);
	}

	if (*name == '\0')
		return ((use_sep == 0) ? 0 : ENODEV);

	if (bcmp(name, sep, len) != 0 || isdigit(name[len]) == 0)
		return (ENODEV);

	name += len;

	if (*name == '0' && name[1] != '\0')
		return (ENODEV);

	for (*c = 0; isdigit(*name) != 0; name++) {
		*c *= 10;
		*c += *name - '0';
		if (*c > dsp_cmax)
			return (ENODEV);
	}

	if (*name != '\0')
		return (ENODEV);

	return (0);
}