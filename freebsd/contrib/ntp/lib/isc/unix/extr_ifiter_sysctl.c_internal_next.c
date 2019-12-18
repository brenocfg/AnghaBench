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
struct ifa_msghdr {scalar_t__ ifam_msglen; } ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {unsigned int pos; int bufused; scalar_t__ buf; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

__attribute__((used)) static isc_result_t
internal_next(isc_interfaceiter_t *iter) {
	struct ifa_msghdr *ifam;
	REQUIRE (iter->pos < (unsigned int) iter->bufused);

	ifam = (struct ifa_msghdr *) ((char *) iter->buf + iter->pos);

	iter->pos += ifam->ifam_msglen;

	if (iter->pos >= iter->bufused)
		return (ISC_R_NOMORE);

	return (ISC_R_SUCCESS);
}