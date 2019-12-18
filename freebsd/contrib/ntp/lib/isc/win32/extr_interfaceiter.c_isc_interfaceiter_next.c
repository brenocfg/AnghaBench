#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_10__ {scalar_t__ result; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 scalar_t__ ISC_R_IGNORE ; 
 scalar_t__ ISC_R_NOMORE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_IFITER (TYPE_1__*) ; 
 scalar_t__ internal_current (TYPE_1__*) ; 
 scalar_t__ internal_current6 (TYPE_1__*) ; 
 scalar_t__ internal_current_GAA (TYPE_1__*) ; 
 scalar_t__ internal_next (TYPE_1__*) ; 
 scalar_t__ internal_next6 (TYPE_1__*) ; 
 scalar_t__ internal_next_GAA (TYPE_1__*) ; 
 scalar_t__ use_GAA ; 
 int use_GAA_determined ; 

isc_result_t
isc_interfaceiter_next(isc_interfaceiter_t *iter) {
	isc_result_t result;

	REQUIRE(VALID_IFITER(iter));
	REQUIRE(iter->result == ISC_R_SUCCESS);
	REQUIRE(use_GAA_determined);

	if (use_GAA) {
		do {
			result = internal_next_GAA(iter);
			if (ISC_R_NOMORE == result)
				goto set_result;
			result = internal_current_GAA(iter);
		} while (ISC_R_IGNORE == result);
		goto set_result;
	}

	for (;;) {
		result = internal_next(iter);
		if (result == ISC_R_NOMORE) {
			result = internal_next6(iter);
			if (result != ISC_R_SUCCESS)
				break;
			result = internal_current6(iter);
			if (result != ISC_R_IGNORE)
				break;
		} else if (result != ISC_R_SUCCESS)
			break;
		result = internal_current(iter);
		if (result != ISC_R_IGNORE)
			break;
	}
 set_result:
	iter->result = result;
	return (result);
}