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
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 scalar_t__ isc__app_register () ; 
 scalar_t__ isc__mem_register () ; 
 scalar_t__ isc__socket_register () ; 
 scalar_t__ isc__task_register () ; 
 scalar_t__ isc__timer_register () ; 

__attribute__((used)) static void
do_register(void) {
	RUNTIME_CHECK(isc__mem_register() == ISC_R_SUCCESS);
	RUNTIME_CHECK(isc__app_register() == ISC_R_SUCCESS);
	RUNTIME_CHECK(isc__task_register() == ISC_R_SUCCESS);
	RUNTIME_CHECK(isc__socket_register() == ISC_R_SUCCESS);
	RUNTIME_CHECK(isc__timer_register() == ISC_R_SUCCESS);
}