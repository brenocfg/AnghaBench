#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/ * size; int /*<<< orphan*/  pci_func; } ;
typedef  TYPE_2__ qlnx_trace_t ;
struct TYPE_7__ {int num_hwfns; } ;
struct TYPE_9__ {TYPE_1__ cdev; int /*<<< orphan*/  pci_func; } ;
typedef  TYPE_3__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qlnx_get_trace_cmd_size (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlnx_get_trace_size(qlnx_host_t *ha, qlnx_trace_t *trace)
{
	int i;

	trace->pci_func = ha->pci_func;

	for (i = 0; i < ha->cdev.num_hwfns; i++) {
		trace->size[i] = qlnx_get_trace_cmd_size(ha, i, trace->cmd);
	}

	return;
}