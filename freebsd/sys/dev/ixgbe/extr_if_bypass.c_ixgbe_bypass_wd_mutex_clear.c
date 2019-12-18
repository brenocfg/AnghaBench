#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  high; } ;
struct adapter {TYPE_1__ bypass; } ;

/* Variables and functions */
 scalar_t__ atomic_cmpset_int (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static void
ixgbe_bypass_wd_mutex_clear(struct adapter *adapter)
{
	while (atomic_cmpset_int(&adapter->bypass.high, 1, 0) == 0)
		usec_delay(6000);
	return;
}