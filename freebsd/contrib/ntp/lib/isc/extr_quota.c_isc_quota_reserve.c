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
struct TYPE_3__ {scalar_t__ max; scalar_t__ used; scalar_t__ soft; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ isc_quota_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_QUOTA ; 
 int /*<<< orphan*/  ISC_R_SOFTQUOTA ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 

isc_result_t
isc_quota_reserve(isc_quota_t *quota) {
	isc_result_t result;
	LOCK(&quota->lock);
	if (quota->max == 0 || quota->used < quota->max) {
		if (quota->soft == 0 || quota->used < quota->soft)
			result = ISC_R_SUCCESS;
		else
			result = ISC_R_SOFTQUOTA;
		quota->used++;
	} else
		result = ISC_R_QUOTA;
	UNLOCK(&quota->lock);
	return (result);
}