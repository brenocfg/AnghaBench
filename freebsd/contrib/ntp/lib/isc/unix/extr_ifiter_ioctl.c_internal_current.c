#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_6__ {int mode; scalar_t__ result6; int /*<<< orphan*/  clua_done; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 scalar_t__ ISC_R_NOMORE ; 
 scalar_t__ internal_current4 (TYPE_1__*) ; 
 scalar_t__ internal_current6 (TYPE_1__*) ; 
 scalar_t__ internal_current_clusteralias (TYPE_1__*) ; 

__attribute__((used)) static isc_result_t
internal_current(isc_interfaceiter_t *iter) {
#if defined(SIOCGLIFCONF) && defined(SIOCGLIFADDR)
	if (iter->mode == 6) {
		iter->result6 = internal_current6(iter);
		if (iter->result6 != ISC_R_NOMORE)
			return (iter->result6);
	}
#endif
#ifdef HAVE_TRUCLUSTER
	if (!iter->clua_done)
		return(internal_current_clusteralias(iter));
#endif
	return (internal_current4(iter));
}