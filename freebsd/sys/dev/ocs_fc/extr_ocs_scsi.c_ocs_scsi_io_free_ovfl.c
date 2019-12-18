#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_4__ {TYPE_3__ ovfl_sgl; int /*<<< orphan*/  ocs; } ;
typedef  TYPE_1__ ocs_io_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_dma_free (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
ocs_scsi_io_free_ovfl(ocs_io_t *io) {
	if (io->ovfl_sgl.size) {
		ocs_dma_free(io->ocs, &io->ovfl_sgl);
	}
}