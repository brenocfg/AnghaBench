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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_2__ {int val; int /*<<< orphan*/ * strval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOTFOUND ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 TYPE_1__* facilities ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char const*) ; 

isc_result_t
isc_syslog_facilityfromstring(const char *str, int *facilityp) {
	int i;

	REQUIRE(str != NULL);
	REQUIRE(facilityp != NULL);

	for (i = 0; facilities[i].strval != NULL; i++) {
		if (strcasecmp(facilities[i].strval, str) == 0) {
			*facilityp = facilities[i].val;
			return (ISC_R_SUCCESS);
		}
	}
	return (ISC_R_NOTFOUND);

}