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
typedef  int isc_fsaccess_t ;

/* Variables and functions */
 int GROUP ; 
 int ISC_FSACCESS_GROUP ; 
 int ISC_FSACCESS_OTHER ; 
 int ISC_FSACCESS_OWNER ; 
 int OTHER ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

void
isc_fsaccess_add(int trustee, int permission, isc_fsaccess_t *access) {
	REQUIRE(trustee <= 0x7);
	REQUIRE(permission <= 0xFF);

	if ((trustee & ISC_FSACCESS_OWNER) != 0)
		*access |= permission;

	if ((trustee & ISC_FSACCESS_GROUP) != 0)
		*access |= (permission << GROUP);

	if ((trustee & ISC_FSACCESS_OTHER) != 0)
		*access |= (permission << OTHER);
}