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

/* Variables and functions */
 scalar_t__ GetCurrentThread () ; 
 int ISC_FALSE ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int blocked ; 
 scalar_t__ blockedthread ; 
 int running ; 

void
isc__app_unblock(void) {
	REQUIRE(running);
	REQUIRE(blocked);
	blocked = ISC_FALSE;
	REQUIRE(blockedthread == GetCurrentThread());
}