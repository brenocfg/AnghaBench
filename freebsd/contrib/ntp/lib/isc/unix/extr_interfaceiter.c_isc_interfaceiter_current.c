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
typedef  scalar_t__ isc_result_t ;
struct TYPE_3__ {scalar_t__ result; int /*<<< orphan*/  current; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;
typedef  int /*<<< orphan*/  isc_interface_t ;

/* Variables and functions */
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

isc_result_t
isc_interfaceiter_current(isc_interfaceiter_t *iter,
			  isc_interface_t *ifdata)
{
	REQUIRE(iter->result == ISC_R_SUCCESS);
	memcpy(ifdata, &iter->current, sizeof(*ifdata));
	return (ISC_R_SUCCESS);
}