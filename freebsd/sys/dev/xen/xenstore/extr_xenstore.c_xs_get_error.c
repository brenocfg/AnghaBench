#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_2__ {int errnum; int /*<<< orphan*/  errstring; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 size_t xsd_error_count ; 
 TYPE_1__* xsd_errors ; 

__attribute__((used)) static int
xs_get_error(const char *errorstring)
{
	u_int i;

	for (i = 0; i < xsd_error_count; i++) {
		if (!strcmp(errorstring, xsd_errors[i].errstring))
			return (xsd_errors[i].errnum);
	}
	log(LOG_WARNING, "XENSTORE xen store gave: unknown error %s",
	    errorstring);
	return (EINVAL);
}