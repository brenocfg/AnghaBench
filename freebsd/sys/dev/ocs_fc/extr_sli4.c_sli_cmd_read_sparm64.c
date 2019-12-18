#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_5__ sli4_t ;
struct TYPE_11__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_12__ {TYPE_2__ data; } ;
struct TYPE_13__ {TYPE_3__ u; int /*<<< orphan*/  buffer_length; int /*<<< orphan*/  bde_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  command; } ;
struct TYPE_15__ {scalar_t__ vpi; TYPE_4__ bde_64; TYPE_1__ hdr; } ;
typedef  TYPE_6__ sli4_cmd_read_sparm64_t ;
struct TYPE_16__ {int /*<<< orphan*/  phys; int /*<<< orphan*/  size; } ;
typedef  TYPE_7__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BDE_TYPE_BDE_64 ; 
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_READ_SPARM64 ; 
 scalar_t__ SLI4_READ_SPARM64_VPI_SPECIAL ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_read_sparm64(sli4_t *sli4, void *buf, size_t size, ocs_dma_t *dma,
		uint16_t vpi)
{
	sli4_cmd_read_sparm64_t	*read_sparm64 = buf;

	ocs_memset(buf, 0, size);

	if (SLI4_READ_SPARM64_VPI_SPECIAL == vpi) {
		ocs_log_test(sli4->os, "special VPI not supported!!!\n");
		return -1;
	}

	if (!dma || !dma->phys) {
		ocs_log_test(sli4->os, "bad DMA buffer\n");
		return -1;
	}

	read_sparm64->hdr.command = SLI4_MBOX_COMMAND_READ_SPARM64;

	read_sparm64->bde_64.bde_type = SLI4_BDE_TYPE_BDE_64;
	read_sparm64->bde_64.buffer_length = dma->size;
	read_sparm64->bde_64.u.data.buffer_address_low  = ocs_addr32_lo(dma->phys);
	read_sparm64->bde_64.u.data.buffer_address_high = ocs_addr32_hi(dma->phys);

	read_sparm64->vpi = vpi;

	return sizeof(sli4_cmd_read_sparm64_t);
}