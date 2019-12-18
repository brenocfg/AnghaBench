#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ dma_cookie_t ;

/* Variables and functions */

__attribute__((used)) static inline bool hidma_txn_is_success(dma_cookie_t cookie,
		dma_cookie_t last_success, dma_cookie_t last_used)
{
	if (last_success <= last_used) {
		if ((cookie <= last_success) || (cookie > last_used))
			return true;
	} else {
		if ((cookie <= last_success) && (cookie > last_used))
			return true;
	}
	return false;
}