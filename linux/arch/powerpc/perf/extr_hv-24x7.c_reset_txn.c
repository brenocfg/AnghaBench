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

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_24x7_txn_err ; 
 int /*<<< orphan*/  hv_24x7_txn_flags ; 

__attribute__((used)) static void reset_txn(void)
{
	__this_cpu_write(hv_24x7_txn_flags, 0);
	__this_cpu_write(hv_24x7_txn_err, 0);
}