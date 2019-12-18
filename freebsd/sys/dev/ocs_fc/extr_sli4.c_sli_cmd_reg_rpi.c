#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  sli4_t ;
struct TYPE_9__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_10__ {TYPE_2__ data; } ;
struct TYPE_11__ {TYPE_3__ u; int /*<<< orphan*/  buffer_length; int /*<<< orphan*/  bde_type; } ;
struct TYPE_8__ {int /*<<< orphan*/  command; } ;
struct TYPE_12__ {void* vpi; TYPE_4__ bde_64; void* etow; void* upd; int /*<<< orphan*/  remote_n_port_id; void* rpi; TYPE_1__ hdr; } ;
typedef  TYPE_5__ sli4_cmd_reg_rpi_t ;
struct TYPE_13__ {int /*<<< orphan*/  phys; } ;
typedef  TYPE_6__ ocs_dma_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BDE_TYPE_BDE_64 ; 
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_REG_RPI ; 
 int /*<<< orphan*/  SLI4_REG_RPI_BUF_LEN ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_reg_rpi(sli4_t *sli4, void *buf, size_t size, uint32_t nport_id, uint16_t rpi, 
			uint16_t vpi, ocs_dma_t *dma, uint8_t update,  uint8_t enable_t10_pi)
{
	sli4_cmd_reg_rpi_t *reg_rpi = buf;

	ocs_memset(buf, 0, size);

	reg_rpi->hdr.command = SLI4_MBOX_COMMAND_REG_RPI;

	reg_rpi->rpi = rpi;
	reg_rpi->remote_n_port_id = nport_id;
	reg_rpi->upd = update;
	reg_rpi->etow = enable_t10_pi;

	reg_rpi->bde_64.bde_type = SLI4_BDE_TYPE_BDE_64;
	reg_rpi->bde_64.buffer_length = SLI4_REG_RPI_BUF_LEN;
	reg_rpi->bde_64.u.data.buffer_address_low  = ocs_addr32_lo(dma->phys);
	reg_rpi->bde_64.u.data.buffer_address_high = ocs_addr32_hi(dma->phys);

	reg_rpi->vpi = vpi;

	return sizeof(sli4_cmd_reg_rpi_t);
}