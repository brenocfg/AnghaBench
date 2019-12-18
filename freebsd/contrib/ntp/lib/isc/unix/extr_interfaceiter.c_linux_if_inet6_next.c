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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {int /*<<< orphan*/  valid; int /*<<< orphan*/ * proc; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/ * fgets (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static isc_result_t
linux_if_inet6_next(isc_interfaceiter_t *iter) {
	if (iter->proc != NULL &&
	    fgets(iter->entry, sizeof(iter->entry), iter->proc) != NULL)
		iter->valid = ISC_R_SUCCESS;
	else
		iter->valid = ISC_R_NOMORE;
	return (iter->valid);
}