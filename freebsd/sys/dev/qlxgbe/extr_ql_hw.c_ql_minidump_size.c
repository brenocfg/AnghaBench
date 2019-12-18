#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {scalar_t__ dma_b; } ;
struct TYPE_8__ {TYPE_1__ minidump; } ;
struct TYPE_9__ {int mdump_capture_mask; TYPE_2__ dma_buf; } ;
struct TYPE_10__ {TYPE_3__ hw; } ;
typedef  TYPE_4__ qla_host_t ;
struct TYPE_11__ {scalar_t__* capture_size_array; } ;
typedef  TYPE_5__ ql_minidump_template_hdr_t ;

/* Variables and functions */
 int QL_DBG_CAP_SIZE_ARRAY_LEN ; 

__attribute__((used)) static uint32_t
ql_minidump_size(qla_host_t *ha)
{
	uint32_t i, k;
	uint32_t size = 0;
	ql_minidump_template_hdr_t *hdr;

	hdr = (ql_minidump_template_hdr_t *)ha->hw.dma_buf.minidump.dma_b;

	i = 0x2;

	for (k = 1; k < QL_DBG_CAP_SIZE_ARRAY_LEN; k++) {
		if (i & ha->hw.mdump_capture_mask)
			size += hdr->capture_size_array[k];
		i = i << 1;
	}
	return (size);
}