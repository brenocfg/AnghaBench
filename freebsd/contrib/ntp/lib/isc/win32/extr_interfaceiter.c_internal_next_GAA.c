#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_7__ {TYPE_1__* ipaaCur; TYPE_2__* ipuaCur; } ;
typedef  TYPE_3__ isc_interfaceiter_t ;
struct TYPE_6__ {struct TYPE_6__* Next; } ;
struct TYPE_5__ {TYPE_2__* FirstUnicastAddress; struct TYPE_5__* Next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOMORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_GAA ; 

__attribute__((used)) static isc_result_t
internal_next_GAA(isc_interfaceiter_t *iter) {
	REQUIRE(use_GAA);
	if (NULL == iter->ipaaCur)
		return (ISC_R_NOMORE);
	if (NULL == iter->ipuaCur)
		iter->ipuaCur = iter->ipaaCur->FirstUnicastAddress;
	else
		iter->ipuaCur = iter->ipuaCur->Next;
	while (NULL == iter->ipuaCur) {
		iter->ipaaCur = iter->ipaaCur->Next;
		if (NULL == iter->ipaaCur)
			return (ISC_R_NOMORE);
		iter->ipuaCur = iter->ipaaCur->FirstUnicastAddress;
	}
	return (ISC_R_SUCCESS);
}