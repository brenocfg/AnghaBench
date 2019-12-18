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
struct TYPE_3__ {int /*<<< orphan*/  magic; scalar_t__ active; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ isc_rwlock_t ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RWLOCK_MAGIC ; 
 int /*<<< orphan*/  UNUSED (unsigned int) ; 
 int /*<<< orphan*/  isc_rwlocktype_read ; 

isc_result_t
isc_rwlock_init(isc_rwlock_t *rwl, unsigned int read_quota,
		unsigned int write_quota)
{
	REQUIRE(rwl != NULL);

	UNUSED(read_quota);
	UNUSED(write_quota);

	rwl->type = isc_rwlocktype_read;
	rwl->active = 0;
	rwl->magic = RWLOCK_MAGIC;

	return (ISC_R_SUCCESS);
}