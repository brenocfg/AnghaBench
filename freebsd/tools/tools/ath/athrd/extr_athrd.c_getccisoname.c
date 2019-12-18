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
struct TYPE_3__ {scalar_t__ countryCode; char const* isoName; } ;
typedef  scalar_t__ HAL_CTRY_CODE ;

/* Variables and functions */
 TYPE_1__* allCountries ; 
 int nitems (TYPE_1__*) ; 

__attribute__((used)) static const char *
getccisoname(HAL_CTRY_CODE cc)
{
	int i;

	for (i = 0; i < nitems(allCountries); i++)
		if (allCountries[i].countryCode == cc)
			return allCountries[i].isoName;
	return NULL;
}