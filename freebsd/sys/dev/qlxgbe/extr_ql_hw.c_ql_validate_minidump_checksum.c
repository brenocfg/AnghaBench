#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int size; int* dma_b; } ;
struct TYPE_7__ {TYPE_1__ minidump; } ;
struct TYPE_8__ {TYPE_2__ dma_buf; } ;
struct TYPE_9__ {TYPE_3__ hw; } ;
typedef  TYPE_4__ qla_host_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
ql_validate_minidump_checksum(qla_host_t *ha)
{
        uint64_t sum = 0;
	int count;
	uint32_t *template_buff;

	count = ha->hw.dma_buf.minidump.size / sizeof (uint32_t);
	template_buff = ha->hw.dma_buf.minidump.dma_b;

	while (count-- > 0) {
		sum += *template_buff++;
	}

	while (sum >> 32) {
		sum = (sum & 0xFFFFFFFF) + (sum >> 32);
	}

	return (~sum);
}