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
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  mbus_state ; 
 int /*<<< orphan*/  mvebu_mbus_disable_window (int /*<<< orphan*/ *,int) ; 
 int mvebu_mbus_find_window (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

int mvebu_mbus_del_window(phys_addr_t base, size_t size)
{
	int win;

	win = mvebu_mbus_find_window(&mbus_state, base, size);
	if (win < 0)
		return win;

	mvebu_mbus_disable_window(&mbus_state, win);
	return 0;
}