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
struct TYPE_4__ {scalar_t__ result6; int /*<<< orphan*/  clua_done; scalar_t__ clua_context; int /*<<< orphan*/  clua_sa; int /*<<< orphan*/  first6; scalar_t__ pos6; scalar_t__ pos; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 int CLUA_SUCCESS ; 
 scalar_t__ ISC_R_NOMORE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_TF (int) ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int clua_getaliasaddress (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  linux_if_inet6_first (TYPE_1__*) ; 

__attribute__((used)) static
void internal_first(isc_interfaceiter_t *iter) {
#ifdef HAVE_TRUCLUSTER
	int clua_result;
#endif
	iter->pos = 0;
#if defined(SIOCGLIFCONF) && defined(SIOCGLIFADDR)
	iter->pos6 = 0;
	if (iter->result6 == ISC_R_NOMORE)
		iter->result6 = ISC_R_SUCCESS;
	iter->first6 = ISC_TRUE;
#endif
#ifdef HAVE_TRUCLUSTER
	iter->clua_context = 0;
	clua_result = clua_getaliasaddress(&iter->clua_sa,
					   &iter->clua_context);
	iter->clua_done = ISC_TF(clua_result != CLUA_SUCCESS);
#endif
#ifdef __linux
	linux_if_inet6_first(iter);
#endif
}