#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ minidump; } ;
struct TYPE_10__ {int /*<<< orphan*/  minidump; TYPE_1__ flags; } ;
struct TYPE_11__ {TYPE_2__ dma_buf; scalar_t__ mdump_init; } ;
struct TYPE_12__ {TYPE_3__ hw; } ;
typedef  TYPE_4__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ql_free_dmabuf (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_free_minidump_buffer (TYPE_4__*) ; 
 int /*<<< orphan*/  ql_free_minidump_template_buffer (TYPE_4__*) ; 

__attribute__((used)) static void
ql_minidump_free(qla_host_t *ha)
{
	ha->hw.mdump_init = 0;
	if (ha->hw.dma_buf.flags.minidump) {
		ha->hw.dma_buf.flags.minidump = 0;
		ql_free_dmabuf(ha, &ha->hw.dma_buf.minidump);
	}

	ql_free_minidump_template_buffer(ha);
	ql_free_minidump_buffer(ha);

	return;
}