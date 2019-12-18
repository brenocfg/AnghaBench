#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_18__ {void* perfh; void* mrqp; void* rxri; void* rxseq; void* hlm; void* iaar; void* fcpc; void* vf; void* dif; void* npiv; void* iaab; } ;
struct TYPE_22__ {TYPE_2__ flag; } ;
struct TYPE_19__ {TYPE_8__ features; scalar_t__ perf_hint; } ;
struct TYPE_16__ {int phys; scalar_t__ size; int /*<<< orphan*/  virt; } ;
struct TYPE_17__ {TYPE_14__ data; } ;
struct TYPE_20__ {int sli_rev; scalar_t__ sli_family; TYPE_3__ config; int /*<<< orphan*/  os; TYPE_1__ vpd; TYPE_14__ bmbx; int /*<<< orphan*/  asic_rev; int /*<<< orphan*/  asic_type; int /*<<< orphan*/  if_type; int /*<<< orphan*/  port_type; } ;
typedef  TYPE_4__ sli4_t ;
typedef  int /*<<< orphan*/  sli4_port_type_e ;
typedef  int /*<<< orphan*/  sli4_mcqe_t ;
struct TYPE_21__ {scalar_t__ rev_id; scalar_t__ family; int /*<<< orphan*/  rev; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ sli4_asic_entry_t ;
typedef  int /*<<< orphan*/  ocs_os_handle_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  SLI4_ASIC_ID_REG ; 
 int SLI4_BMBX_MASK_LO ; 
 int SLI4_BMBX_SIZE ; 
 scalar_t__ SLI4_FAMILY_CHECK_ASIC_TYPE ; 
 int /*<<< orphan*/  SLI4_IF_TYPE_LANCER_FC_ETH ; 
 int /*<<< orphan*/  SLI4_INTF_REG ; 
 int /*<<< orphan*/  SLI4_PCI_CLASS_REVISION ; 
 int /*<<< orphan*/  SLI4_REG_SLIPORT_ERROR1 ; 
 int /*<<< orphan*/  SLI4_REG_SLIPORT_ERROR2 ; 
 int /*<<< orphan*/  SLI4_REG_SLIPORT_STATUS ; 
 void* TRUE ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  ocs_addr32_hi (int) ; 
 int /*<<< orphan*/  ocs_addr32_lo (int) ; 
 scalar_t__ ocs_config_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_dma_alloc (int /*<<< orphan*/ ,TYPE_14__*,int,int) ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* sli4_asic_table ; 
 scalar_t__ sli_asic_gen (scalar_t__) ; 
 scalar_t__ sli_fw_init (TYPE_4__*) ; 
 scalar_t__ sli_get_config (TYPE_4__*) ; 
 int /*<<< orphan*/  sli_intf_if_type (scalar_t__) ; 
 scalar_t__ sli_intf_sli_family (scalar_t__) ; 
 int sli_intf_sli_revision (scalar_t__) ; 
 scalar_t__ sli_intf_valid_check (scalar_t__) ; 
 scalar_t__ sli_pci_rev_id (scalar_t__) ; 
 int /*<<< orphan*/  sli_reg_read (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sli_request_features (TYPE_4__*,TYPE_8__*,void*) ; 

int32_t
sli_setup(sli4_t *sli4, ocs_os_handle_t os, sli4_port_type_e port_type)
{
	uint32_t sli_intf = UINT32_MAX;
	uint32_t pci_class_rev = 0;
	uint32_t rev_id = 0;
	uint32_t family = 0;
	uint32_t i;
	sli4_asic_entry_t *asic;

	ocs_memset(sli4, 0, sizeof(sli4_t));

	sli4->os = os;
	sli4->port_type = port_type;

	/*
	 * Read the SLI_INTF register to discover the register layout
	 * and other capability information
	 */
	sli_intf = ocs_config_read32(os, SLI4_INTF_REG);

	if (sli_intf_valid_check(sli_intf)) {
		ocs_log_err(os, "SLI_INTF is not valid\n");
		return -1;
	}

	/* driver only support SLI-4 */
	sli4->sli_rev = sli_intf_sli_revision(sli_intf);
	if (4 != sli4->sli_rev) {
		ocs_log_err(os, "Unsupported SLI revision (intf=%#x)\n",
				sli_intf);
		return -1;
	}

	sli4->sli_family = sli_intf_sli_family(sli_intf);

	sli4->if_type = sli_intf_if_type(sli_intf);

	if (SLI4_IF_TYPE_LANCER_FC_ETH == sli4->if_type) {
		ocs_log_debug(os, "status=%#x error1=%#x error2=%#x\n",
				sli_reg_read(sli4, SLI4_REG_SLIPORT_STATUS),
				sli_reg_read(sli4, SLI4_REG_SLIPORT_ERROR1),
				sli_reg_read(sli4, SLI4_REG_SLIPORT_ERROR2));
	}

	/*
	 * set the ASIC type and revision
	 */
	pci_class_rev = ocs_config_read32(os, SLI4_PCI_CLASS_REVISION);
	rev_id = sli_pci_rev_id(pci_class_rev);
	family = sli4->sli_family;
	if (family == SLI4_FAMILY_CHECK_ASIC_TYPE) {
		uint32_t asic_id = ocs_config_read32(os, SLI4_ASIC_ID_REG);
		family = sli_asic_gen(asic_id);
	}

	for (i = 0, asic = sli4_asic_table; i < ARRAY_SIZE(sli4_asic_table); i++, asic++) {
		if ((rev_id == asic->rev_id) && (family == asic->family)) {
			sli4->asic_type = asic->type;
			sli4->asic_rev = asic->rev;
			break;
		}
	}
	/* Fail if no matching asic type/rev was found */
	if( (sli4->asic_type == 0) || (sli4->asic_rev == 0)) {
		ocs_log_err(os, "no matching asic family/rev found: %02x/%02x\n", family, rev_id);
		return -1;
	}

	/*
	 * The bootstrap mailbox is equivalent to a MQ with a single 256 byte
	 * entry, a CQ with a single 16 byte entry, and no event queue.
	 * Alignment must be 16 bytes as the low order address bits in the
	 * address register are also control / status.
	 */
	if (ocs_dma_alloc(sli4->os, &sli4->bmbx, SLI4_BMBX_SIZE +
				sizeof(sli4_mcqe_t), 16)) {
		ocs_log_err(os, "bootstrap mailbox allocation failed\n");
		return -1;
	}

	if (sli4->bmbx.phys & SLI4_BMBX_MASK_LO) {
		ocs_log_err(os, "bad alignment for bootstrap mailbox\n");
		return -1;
	}

	ocs_log_debug(os, "bmbx v=%p p=0x%x %08x s=%zd\n", sli4->bmbx.virt,
		ocs_addr32_hi(sli4->bmbx.phys),
		ocs_addr32_lo(sli4->bmbx.phys),
		sli4->bmbx.size);

	/* TODO 4096 is arbitrary. What should this value actually be? */
	if (ocs_dma_alloc(sli4->os, &sli4->vpd.data, 4096/*TODO*/, 4096)) {
		/* Note that failure isn't fatal in this specific case */
		sli4->vpd.data.size = 0;
		ocs_log_test(os, "VPD buffer allocation failed\n");
	}

	if (sli_fw_init(sli4)) {
		ocs_log_err(sli4->os, "FW initialization failed\n");
		return -1;
	}

	/*
	 * Set one of fcpi(initiator), fcpt(target), fcpc(combined) to true
	 * in addition to any other desired features
	 */
	sli4->config.features.flag.iaab = TRUE;
	sli4->config.features.flag.npiv = TRUE;
	sli4->config.features.flag.dif = TRUE;
	sli4->config.features.flag.vf = TRUE;
	sli4->config.features.flag.fcpc = TRUE;
	sli4->config.features.flag.iaar = TRUE;
	sli4->config.features.flag.hlm = TRUE;
	sli4->config.features.flag.perfh = TRUE;
	sli4->config.features.flag.rxseq = TRUE;
	sli4->config.features.flag.rxri = TRUE;
	sli4->config.features.flag.mrqp = TRUE;

	/* use performance hints if available */
	if (sli4->config.perf_hint) {
		sli4->config.features.flag.perfh = TRUE;
	}

	if (sli_request_features(sli4, &sli4->config.features, TRUE)) {
		return -1;
	}

	if (sli_get_config(sli4)) {
		return -1;
	}

	return 0;
}