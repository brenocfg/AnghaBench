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
 int /*<<< orphan*/  _thr_umutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addr_lock ; 
 int /*<<< orphan*/ * wake_addr_head ; 

void
_thr_wake_addr_init(void)
{
	_thr_umutex_init(&addr_lock);
	wake_addr_head = NULL;
}