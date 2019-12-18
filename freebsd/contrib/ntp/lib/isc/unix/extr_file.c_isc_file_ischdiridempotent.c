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
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ isc_file_isabsolute (char const*) ; 
 scalar_t__ isc_file_iscurrentdir (char const*) ; 

isc_boolean_t
isc_file_ischdiridempotent(const char *filename) {
	REQUIRE(filename != NULL);
	if (isc_file_isabsolute(filename))
		return (ISC_TRUE);
	if (isc_file_iscurrentdir(filename))
		return (ISC_TRUE);
	return (ISC_FALSE);
}