#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_6__ {int sa_len; } ;
struct ifreq {TYPE_1__ ifr_addr; } ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_7__ {scalar_t__ ifc_len; scalar_t__ ifc_req; } ;
struct TYPE_8__ {unsigned int pos; TYPE_2__ ifc; } ;
typedef  TYPE_3__ isc_interfaceiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_R_NOMORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  linux_if_inet6_next (TYPE_3__*) ; 

__attribute__((used)) static isc_result_t
internal_next4(isc_interfaceiter_t *iter) {
#ifdef ISC_PLATFORM_HAVESALEN
	struct ifreq *ifrp;
#endif

	if (iter->pos < (unsigned int) iter->ifc.ifc_len) {
#ifdef ISC_PLATFORM_HAVESALEN
		ifrp = (struct ifreq *)((char *) iter->ifc.ifc_req + iter->pos);

		if (ifrp->ifr_addr.sa_len > sizeof(struct sockaddr))
			iter->pos += sizeof(ifrp->ifr_name) +
				     ifrp->ifr_addr.sa_len;
		else
#endif
			iter->pos += sizeof(struct ifreq);

	} else {
		INSIST(iter->pos == (unsigned int) iter->ifc.ifc_len);
#ifdef __linux
		return (linux_if_inet6_next(iter));
#else
		return (ISC_R_NOMORE);
#endif
	}
	return (ISC_R_SUCCESS);
}