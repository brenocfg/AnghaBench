#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  io_lock; } ;
typedef  TYPE_1__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/ * _ocs_hw_io_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

ocs_hw_io_t *
ocs_hw_io_alloc(ocs_hw_t *hw)
{
	ocs_hw_io_t	*io = NULL;

	ocs_lock(&hw->io_lock);
		io = _ocs_hw_io_alloc(hw);
	ocs_unlock(&hw->io_lock);

	return io;
}