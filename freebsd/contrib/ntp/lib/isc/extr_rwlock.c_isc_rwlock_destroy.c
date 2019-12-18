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
struct TYPE_3__ {scalar_t__ active; scalar_t__ magic; } ;
typedef  TYPE_1__ isc_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 

void
isc_rwlock_destroy(isc_rwlock_t *rwl) {
	REQUIRE(rwl != NULL);
	REQUIRE(rwl->active == 0);
	rwl->magic = 0;
}