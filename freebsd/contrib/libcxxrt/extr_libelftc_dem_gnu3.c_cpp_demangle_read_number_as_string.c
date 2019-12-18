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
struct cpp_demangle_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,long) ; 
 int /*<<< orphan*/  cpp_demangle_read_number (struct cpp_demangle_data*,long*) ; 

__attribute__((used)) static int
cpp_demangle_read_number_as_string(struct cpp_demangle_data *ddata, char **str)
{
	long n;

	if (!cpp_demangle_read_number(ddata, &n)) {
		*str = NULL;
		return (0);
	}

	if (asprintf(str, "%ld", n) < 0) {
		*str = NULL;
		return (0);
	}

	return (1);
}