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
struct TYPE_9__ {int /*<<< orphan*/  dma_b; } ;
struct TYPE_10__ {TYPE_1__ minidump; } ;
struct TYPE_11__ {int mdump_done; int /*<<< orphan*/  mdump_start_seq_index; int /*<<< orphan*/  mdump_template_size; int /*<<< orphan*/  mdump_template; TYPE_2__ dma_buf; int /*<<< orphan*/  mdump_buffer_size; int /*<<< orphan*/  mdump_buffer; int /*<<< orphan*/  mdump_usec_ts; int /*<<< orphan*/  mdump_init; } ;
struct TYPE_12__ {TYPE_3__ hw; } ;
typedef  TYPE_4__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_parse_template (TYPE_4__*) ; 
 int /*<<< orphan*/  ql_start_sequence (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_stop_sequence (TYPE_4__*) ; 
 int /*<<< orphan*/  qla_get_usec_timestamp () ; 

void
ql_minidump(qla_host_t *ha)
{
	if (!ha->hw.mdump_init)
		return;

	if (ha->hw.mdump_done)
		return;
	ha->hw.mdump_usec_ts = qla_get_usec_timestamp();
	ha->hw.mdump_start_seq_index = ql_stop_sequence(ha);

	bzero(ha->hw.mdump_buffer, ha->hw.mdump_buffer_size);
	bzero(ha->hw.mdump_template, ha->hw.mdump_template_size);

	bcopy(ha->hw.dma_buf.minidump.dma_b, ha->hw.mdump_template,
		ha->hw.mdump_template_size);

	ql_parse_template(ha);
 
	ql_start_sequence(ha, ha->hw.mdump_start_seq_index);

	ha->hw.mdump_done = 1;

	return;
}