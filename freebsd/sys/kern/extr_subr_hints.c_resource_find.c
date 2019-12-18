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
 int ENOENT ; 
 int res_find (char**,int*,int*,char const*,int*,char const*,char const*,char const**,int*,int*,char const**,int*,char const**) ; 

__attribute__((used)) static int
resource_find(int *line, int *startln,
    const char *name, int *unit, const char *resname, const char *value,
    const char **ret_name, int *ret_namelen, int *ret_unit,
    const char **ret_resname, int *ret_resnamelen, const char **ret_value)
{
	int i;
	int un;
	char *hintp;

	*line = 0;
	hintp = NULL;

	/* Search for exact unit matches first */
	i = res_find(&hintp, line, startln, name, unit, resname, value,
	    ret_name, ret_namelen, ret_unit, ret_resname, ret_resnamelen,
	    ret_value);
	if (i == 0)
		return 0;
	if (unit == NULL)
		return ENOENT;
	/* If we are still here, search for wildcard matches */
	un = -1;
	i = res_find(&hintp, line, startln, name, &un, resname, value,
	    ret_name, ret_namelen, ret_unit, ret_resname, ret_resnamelen,
	    ret_value);
	if (i == 0)
		return 0;
	return ENOENT;
}