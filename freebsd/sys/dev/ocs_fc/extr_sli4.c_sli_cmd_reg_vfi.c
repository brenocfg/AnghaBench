#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  r_a_tov; int /*<<< orphan*/  e_d_tov; } ;
struct TYPE_21__ {TYPE_6__ config; } ;
typedef  TYPE_8__ sli4_t ;
struct TYPE_15__ {int /*<<< orphan*/  buffer_address_high; int /*<<< orphan*/  buffer_address_low; } ;
struct TYPE_16__ {TYPE_2__ data; } ;
struct TYPE_17__ {int buffer_length; TYPE_3__ u; int /*<<< orphan*/  bde_type; } ;
struct TYPE_14__ {int /*<<< orphan*/  command; } ;
struct TYPE_22__ {int /*<<< orphan*/  local_n_port_id; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  vpi; int /*<<< orphan*/  vp; int /*<<< orphan*/  r_a_tov; int /*<<< orphan*/  e_d_tov; TYPE_4__ sparm; int /*<<< orphan*/  fcfi; int /*<<< orphan*/  vfi; TYPE_1__ hdr; } ;
typedef  TYPE_9__ sli4_cmd_reg_vfi_t ;
struct TYPE_18__ {int /*<<< orphan*/  phys; } ;
struct TYPE_13__ {TYPE_7__* sport; TYPE_5__ dma; int /*<<< orphan*/  fcf_indicator; int /*<<< orphan*/  indicator; } ;
typedef  TYPE_10__ ocs_domain_t ;
typedef  int int32_t ;
struct TYPE_20__ {int /*<<< orphan*/  fc_id; int /*<<< orphan*/  sli_wwpn; int /*<<< orphan*/  indicator; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BDE_TYPE_BDE_64 ; 
 int /*<<< orphan*/  SLI4_MBOX_COMMAND_REG_VFI ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_addr32_hi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_memset (void*,int /*<<< orphan*/ ,size_t) ; 

int32_t
sli_cmd_reg_vfi(sli4_t *sli4, void *buf, size_t size, ocs_domain_t *domain)
{
	sli4_cmd_reg_vfi_t	*reg_vfi = buf;

	if (!sli4 || !buf || !domain) {
		return 0;
	}

	ocs_memset(buf, 0, size);

	reg_vfi->hdr.command = SLI4_MBOX_COMMAND_REG_VFI;

	reg_vfi->vfi = domain->indicator;

	reg_vfi->fcfi = domain->fcf_indicator;

	/* TODO contents of domain->dma only valid if topo == FABRIC */
	reg_vfi->sparm.bde_type = SLI4_BDE_TYPE_BDE_64;
	reg_vfi->sparm.buffer_length = 0x70;
	reg_vfi->sparm.u.data.buffer_address_low  = ocs_addr32_lo(domain->dma.phys);
	reg_vfi->sparm.u.data.buffer_address_high = ocs_addr32_hi(domain->dma.phys);

	reg_vfi->e_d_tov = sli4->config.e_d_tov;
	reg_vfi->r_a_tov = sli4->config.r_a_tov;

	reg_vfi->vp = TRUE;
	reg_vfi->vpi = domain->sport->indicator;
	ocs_memcpy(reg_vfi->wwpn, &domain->sport->sli_wwpn, sizeof(reg_vfi->wwpn));
	reg_vfi->local_n_port_id = domain->sport->fc_id;

	return sizeof(sli4_cmd_reg_vfi_t);
}