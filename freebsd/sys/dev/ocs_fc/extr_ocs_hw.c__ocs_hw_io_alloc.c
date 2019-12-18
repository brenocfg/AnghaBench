#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  io_alloc_failed_count; int /*<<< orphan*/  io_inuse; int /*<<< orphan*/  io_free; } ;
typedef  TYPE_1__ ocs_hw_t ;
struct TYPE_9__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  abort_reqtag; int /*<<< orphan*/  quarantine_first_phase; int /*<<< orphan*/  quarantine; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ ocs_hw_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OCS_HW_IO_STATE_INUSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  ocs_atomic_add_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_hw_io_free_internal ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* ocs_list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static inline ocs_hw_io_t *
_ocs_hw_io_alloc(ocs_hw_t *hw)
{
	ocs_hw_io_t	*io = NULL;

	if (NULL != (io = ocs_list_remove_head(&hw->io_free))) {
		ocs_list_add_tail(&hw->io_inuse, io);
		io->state = OCS_HW_IO_STATE_INUSE;
		io->quarantine = FALSE;
		io->quarantine_first_phase = TRUE;
		io->abort_reqtag = UINT32_MAX;
		ocs_ref_init(&io->ref, ocs_hw_io_free_internal, io);
	} else {
		ocs_atomic_add_return(&hw->io_alloc_failed_count, 1);
	}

	return io;
}