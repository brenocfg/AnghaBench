#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int errnum; char const* errstring; } ;

/* Variables and functions */
 unsigned int nitems (TYPE_1__*) ; 
 TYPE_1__* xsd_errors ; 

__attribute__((used)) static const char *
xs_dev_error_to_string(int error)
{
	unsigned int i;

	for (i = 0; i < nitems(xsd_errors); i++)
		if (xsd_errors[i].errnum == error)
			return (xsd_errors[i].errstring);

	return (NULL);
}