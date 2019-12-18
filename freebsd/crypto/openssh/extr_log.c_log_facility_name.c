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
struct TYPE_2__ {char const* name; scalar_t__ val; } ;
typedef  scalar_t__ SyslogFacility ;

/* Variables and functions */
 TYPE_1__* log_facilities ; 

const char *
log_facility_name(SyslogFacility facility)
{
	u_int i;

	for (i = 0;  log_facilities[i].name; i++)
		if (log_facilities[i].val == facility)
			return log_facilities[i].name;
	return NULL;
}