#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
struct TYPE_5__ {int mode; scalar_t__ result6; scalar_t__ clua_done; int /*<<< orphan*/  clua_context; int /*<<< orphan*/  clua_sa; scalar_t__ first6; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 int CLUA_SUCCESS ; 
 scalar_t__ ISC_FALSE ; 
 scalar_t__ ISC_R_NOMORE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ ISC_TRUE ; 
 int clua_getaliasaddress (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ internal_next4 (TYPE_1__*) ; 
 scalar_t__ internal_next6 (TYPE_1__*) ; 

__attribute__((used)) static isc_result_t
internal_next(isc_interfaceiter_t *iter) {
#ifdef HAVE_TRUCLUSTER
	int clua_result;
#endif
#if defined(SIOCGLIFCONF) && defined(SIOCGLIFADDR)
	if (iter->mode == 6) {
		iter->result6 = internal_next6(iter);
		if (iter->result6 != ISC_R_NOMORE)
			return (iter->result6);
		if (iter->first6) {
			iter->first6 = ISC_FALSE;
			return (ISC_R_SUCCESS);
		}
	}
#endif
#ifdef HAVE_TRUCLUSTER
	if (!iter->clua_done) {
		clua_result = clua_getaliasaddress(&iter->clua_sa,
						   &iter->clua_context);
		if (clua_result != CLUA_SUCCESS)
			iter->clua_done = ISC_TRUE;
		return (ISC_R_SUCCESS);
	}
#endif
	return (internal_next4(iter));
}