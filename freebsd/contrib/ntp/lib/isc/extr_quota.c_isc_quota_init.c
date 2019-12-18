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
struct TYPE_3__ {int max; int /*<<< orphan*/  lock; scalar_t__ soft; scalar_t__ used; } ;
typedef  TYPE_1__ isc_quota_t ;

/* Variables and functions */
 int /*<<< orphan*/  isc_mutex_init (int /*<<< orphan*/ *) ; 

isc_result_t
isc_quota_init(isc_quota_t *quota, int max) {
	quota->max = max;
	quota->used = 0;
	quota->soft = 0;
	return (isc_mutex_init(&quota->lock));
}