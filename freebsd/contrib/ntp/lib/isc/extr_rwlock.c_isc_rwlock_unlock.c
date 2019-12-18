#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_rwlocktype_t ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ active; } ;
typedef  TYPE_1__ isc_rwlock_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNUSED (scalar_t__) ; 
 int VALID_RWLOCK (TYPE_1__*) ; 

isc_result_t
isc_rwlock_unlock(isc_rwlock_t *rwl, isc_rwlocktype_t type) {
	REQUIRE(VALID_RWLOCK(rwl));
	REQUIRE(rwl->type == type);

	UNUSED(type);

	INSIST(rwl->active > 0);
	rwl->active--;

	return (ISC_R_SUCCESS);
}