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
struct cpp_demangle_data {char* cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int cpp_demangle_get_tmpl_param (struct cpp_demangle_data*,long) ; 
 scalar_t__ errno ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static int
cpp_demangle_read_tmpl_param(struct cpp_demangle_data *ddata)
{
	long nth;

	if (ddata == NULL || *ddata->cur != 'T')
		return (0);

	++ddata->cur;

	if (*ddata->cur == '_')
		return (cpp_demangle_get_tmpl_param(ddata, 0));
	else {

		errno = 0;
		if ((nth = strtol(ddata->cur, (char **) NULL, 36)) == 0 &&
		    errno != 0)
			return (0);

		/* T_ is first */
		++nth;

		while (*ddata->cur != '_')
			++ddata->cur;

		assert(nth > 0);

		return (cpp_demangle_get_tmpl_param(ddata, nth));
	}

	/* NOTREACHED */
	return (0);
}