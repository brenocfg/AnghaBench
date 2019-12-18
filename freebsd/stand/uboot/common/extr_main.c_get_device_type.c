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
struct device_type {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int DEV_TYP_NONE ; 
 struct device_type* device_types ; 
 int nitems (struct device_type*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static const char *
get_device_type(const char *devstr, int *devtype)
{
	int i;
	int namelen;
	struct device_type *dt;

	if (devstr) {
		for (i = 0; i < nitems(device_types); i++) {
			dt = &device_types[i];
			namelen = strlen(dt->name);
			if (strncmp(dt->name, devstr, namelen) == 0) {
				*devtype = dt->type;
				return (devstr + namelen);
			}
		}
		printf("Unknown device type '%s'\n", devstr);
	}

	*devtype = DEV_TYP_NONE;
	return (NULL);
}