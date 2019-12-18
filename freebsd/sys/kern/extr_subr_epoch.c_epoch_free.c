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
typedef  TYPE_1__* epoch_t ;
struct TYPE_5__ {size_t e_idx; int /*<<< orphan*/  e_drain_sx; int /*<<< orphan*/  e_drain_mtx; int /*<<< orphan*/  e_pcpu_record; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_EPOCH ; 
 int /*<<< orphan*/ ** allepochs ; 
 int /*<<< orphan*/  epoch_drain_callbacks (TYPE_1__*) ; 
 int /*<<< orphan*/  epoch_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_epoch ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcpu_zone_record ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree_pcpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
epoch_free(epoch_t epoch)
{

	epoch_drain_callbacks(epoch);
	allepochs[epoch->e_idx] = NULL;
	epoch_wait(global_epoch);
	uma_zfree_pcpu(pcpu_zone_record, epoch->e_pcpu_record);
	mtx_destroy(&epoch->e_drain_mtx);
	sx_destroy(&epoch->e_drain_sx);
	free(epoch, M_EPOCH);
}