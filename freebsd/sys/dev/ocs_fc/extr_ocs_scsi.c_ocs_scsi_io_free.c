#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  display_name; } ;
typedef  TYPE_1__ ocs_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_assert (int) ; 
 int /*<<< orphan*/  ocs_ref_put (int /*<<< orphan*/ *) ; 
 scalar_t__ ocs_ref_read_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_io_trace (TYPE_1__*,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
ocs_scsi_io_free(ocs_io_t *io)
{
	scsi_io_trace(io, "freeing io 0x%p %s\n", io, io->display_name);
	ocs_assert(ocs_ref_read_count(&io->ref) > 0);
	ocs_ref_put(&io->ref); /* ocs_ref_get(): ocs_scsi_io_alloc() */
}