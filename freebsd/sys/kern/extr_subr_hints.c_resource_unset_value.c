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
typedef  int /*<<< orphan*/  varname ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int kern_unsetenv (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int resource_find (int*,int /*<<< orphan*/ *,char const*,int*,char const*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
resource_unset_value(const char *name, int unit, const char *resname)
{
	char varname[128];
	const char *retname, *retvalue;
	int error, line;
	size_t len;

	line = 0;
	error = resource_find(&line, NULL, name, &unit, resname, NULL,
	    &retname, NULL, NULL, NULL, NULL, &retvalue);
	if (error)
		return (error);

	retname -= strlen("hint.");
	len = retvalue - retname - 1;
	if (len > sizeof(varname) - 1)
		return (ENAMETOOLONG);
	memcpy(varname, retname, len);
	varname[len] = '\0';
	return (kern_unsetenv(varname));
}