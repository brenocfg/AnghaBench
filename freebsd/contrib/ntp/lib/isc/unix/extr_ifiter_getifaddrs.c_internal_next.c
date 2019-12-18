#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_6__ {TYPE_1__* pos; } ;
typedef  TYPE_2__ isc_interfaceiter_t ;
struct TYPE_5__ {struct TYPE_5__* ifa_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  linux_if_inet6_next (TYPE_2__*) ; 
 int /*<<< orphan*/  seenv6 ; 

__attribute__((used)) static isc_result_t
internal_next(isc_interfaceiter_t *iter) {

	if (iter->pos != NULL)
		iter->pos = iter->pos->ifa_next;
	if (iter->pos == NULL) {
#ifdef __linux
		if (!seenv6)
			return (linux_if_inet6_next(iter));
#endif
		return (ISC_R_NOMORE);
	}

	return (ISC_R_SUCCESS);
}