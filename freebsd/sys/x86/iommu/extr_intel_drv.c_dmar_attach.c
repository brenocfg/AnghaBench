#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct dmar_unit {int hw_cap; int hw_ecap; int /*<<< orphan*/  ctx_obj; int /*<<< orphan*/  domids; int /*<<< orphan*/  domains; int /*<<< orphan*/  lock; TYPE_1__* intrs; int /*<<< orphan*/  hw_ver; int /*<<< orphan*/ * regs; int /*<<< orphan*/  reg_rid; int /*<<< orphan*/  base; int /*<<< orphan*/  segment; int /*<<< orphan*/  unit; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int /*<<< orphan*/  Address; int /*<<< orphan*/  Segment; } ;
struct TYPE_5__ {int irq; char* name; int /*<<< orphan*/  disable_intr; int /*<<< orphan*/  enable_intr; int /*<<< orphan*/  msi_uaddr_reg; int /*<<< orphan*/  msi_addr_reg; int /*<<< orphan*/  msi_data_reg; int /*<<< orphan*/  handler; int /*<<< orphan*/  irq_rid; } ;
typedef  TYPE_2__ ACPI_DMAR_HARDWARE_UNIT ;

/* Variables and functions */
 int DMAR_CAP_CM ; 
 int /*<<< orphan*/  DMAR_CAP_ND (int) ; 
 int /*<<< orphan*/  DMAR_CAP_REG ; 
 scalar_t__ DMAR_CTX_CNT ; 
 int DMAR_ECAP_DI ; 
 int /*<<< orphan*/  DMAR_ECAP_REG ; 
 int /*<<< orphan*/  DMAR_FAULT_IRQ_RID ; 
 int /*<<< orphan*/  DMAR_FEADDR_REG ; 
 int /*<<< orphan*/  DMAR_FEDATA_REG ; 
 int /*<<< orphan*/  DMAR_FEUADDR_REG ; 
 scalar_t__ DMAR_HAS_QI (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_IEADDR_REG ; 
 int /*<<< orphan*/  DMAR_IEDATA_REG ; 
 int /*<<< orphan*/  DMAR_IEUADDR_REG ; 
 size_t DMAR_INTR_FAULT ; 
 size_t DMAR_INTR_QI ; 
 int DMAR_INTR_TOTAL ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int DMAR_PGF_WAITOK ; 
 int DMAR_PGF_ZERO ; 
 int /*<<< orphan*/  DMAR_QI_IRQ_RID ; 
 int /*<<< orphan*/  DMAR_REG_RID ; 
 int /*<<< orphan*/  DMAR_UNLOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  DMAR_VER_REG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IDX_TO_OFF (scalar_t__) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OBJT_PHYS ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TUNABLE_UINT64_FETCH (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_unr_specific (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dmar_unit* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int dmar_alloc_irq (int /*<<< orphan*/ ,struct dmar_unit*,size_t) ; 
 int /*<<< orphan*/  dmar_disable_fault_intr ; 
 int /*<<< orphan*/  dmar_disable_qi_intr ; 
 int /*<<< orphan*/  dmar_enable_fault_intr ; 
 int /*<<< orphan*/  dmar_enable_qi_intr ; 
 int dmar_enable_translation (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_fault_intr ; 
 TYPE_2__* dmar_find_by_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_get_timeout () ; 
 int dmar_init_busdma (struct dmar_unit*) ; 
 int dmar_init_fault_log (struct dmar_unit*) ; 
 int dmar_init_irt (struct dmar_unit*) ; 
 int dmar_init_qi (struct dmar_unit*) ; 
 int dmar_inv_ctx_glob (struct dmar_unit*) ; 
 int dmar_inv_iotlb_glob (struct dmar_unit*) ; 
 int dmar_load_root_entry_ptr (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_nd2mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_pgalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmar_print_caps (int /*<<< orphan*/ ,struct dmar_unit*,TYPE_2__*) ; 
 int /*<<< orphan*/  dmar_qi_intr ; 
 int /*<<< orphan*/  dmar_quirks_post_ident (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_read4 (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 void* dmar_read8 (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_release_resources (int /*<<< orphan*/ ,struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_update_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_pager_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dmar_attach(device_t dev)
{
	struct dmar_unit *unit;
	ACPI_DMAR_HARDWARE_UNIT *dmaru;
	uint64_t timeout;
	int i, error;

	unit = device_get_softc(dev);
	unit->dev = dev;
	unit->unit = device_get_unit(dev);
	dmaru = dmar_find_by_index(unit->unit);
	if (dmaru == NULL)
		return (EINVAL);
	unit->segment = dmaru->Segment;
	unit->base = dmaru->Address;
	unit->reg_rid = DMAR_REG_RID;
	unit->regs = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &unit->reg_rid, RF_ACTIVE);
	if (unit->regs == NULL) {
		device_printf(dev, "cannot allocate register window\n");
		return (ENOMEM);
	}
	unit->hw_ver = dmar_read4(unit, DMAR_VER_REG);
	unit->hw_cap = dmar_read8(unit, DMAR_CAP_REG);
	unit->hw_ecap = dmar_read8(unit, DMAR_ECAP_REG);
	if (bootverbose)
		dmar_print_caps(dev, unit, dmaru);
	dmar_quirks_post_ident(unit);

	timeout = dmar_get_timeout();
	TUNABLE_UINT64_FETCH("hw.dmar.timeout", &timeout);
	dmar_update_timeout(timeout);

	for (i = 0; i < DMAR_INTR_TOTAL; i++)
		unit->intrs[i].irq = -1;

	unit->intrs[DMAR_INTR_FAULT].name = "fault";
	unit->intrs[DMAR_INTR_FAULT].irq_rid = DMAR_FAULT_IRQ_RID;
	unit->intrs[DMAR_INTR_FAULT].handler = dmar_fault_intr;
	unit->intrs[DMAR_INTR_FAULT].msi_data_reg = DMAR_FEDATA_REG;
	unit->intrs[DMAR_INTR_FAULT].msi_addr_reg = DMAR_FEADDR_REG;
	unit->intrs[DMAR_INTR_FAULT].msi_uaddr_reg = DMAR_FEUADDR_REG;
	unit->intrs[DMAR_INTR_FAULT].enable_intr = dmar_enable_fault_intr;
	unit->intrs[DMAR_INTR_FAULT].disable_intr = dmar_disable_fault_intr;
	error = dmar_alloc_irq(dev, unit, DMAR_INTR_FAULT);
	if (error != 0) {
		dmar_release_resources(dev, unit);
		return (error);
	}
	if (DMAR_HAS_QI(unit)) {
		unit->intrs[DMAR_INTR_QI].name = "qi";
		unit->intrs[DMAR_INTR_QI].irq_rid = DMAR_QI_IRQ_RID;
		unit->intrs[DMAR_INTR_QI].handler = dmar_qi_intr;
		unit->intrs[DMAR_INTR_QI].msi_data_reg = DMAR_IEDATA_REG;
		unit->intrs[DMAR_INTR_QI].msi_addr_reg = DMAR_IEADDR_REG;
		unit->intrs[DMAR_INTR_QI].msi_uaddr_reg = DMAR_IEUADDR_REG;
		unit->intrs[DMAR_INTR_QI].enable_intr = dmar_enable_qi_intr;
		unit->intrs[DMAR_INTR_QI].disable_intr = dmar_disable_qi_intr;
		error = dmar_alloc_irq(dev, unit, DMAR_INTR_QI);
		if (error != 0) {
			dmar_release_resources(dev, unit);
			return (error);
		}
	}

	mtx_init(&unit->lock, "dmarhw", NULL, MTX_DEF);
	unit->domids = new_unrhdr(0, dmar_nd2mask(DMAR_CAP_ND(unit->hw_cap)),
	    &unit->lock);
	LIST_INIT(&unit->domains);

	/*
	 * 9.2 "Context Entry":
	 * When Caching Mode (CM) field is reported as Set, the
	 * domain-id value of zero is architecturally reserved.
	 * Software must not use domain-id value of zero
	 * when CM is Set.
	 */
	if ((unit->hw_cap & DMAR_CAP_CM) != 0)
		alloc_unr_specific(unit->domids, 0);

	unit->ctx_obj = vm_pager_allocate(OBJT_PHYS, NULL, IDX_TO_OFF(1 +
	    DMAR_CTX_CNT), 0, 0, NULL);

	/*
	 * Allocate and load the root entry table pointer.  Enable the
	 * address translation after the required invalidations are
	 * done.
	 */
	dmar_pgalloc(unit->ctx_obj, 0, DMAR_PGF_WAITOK | DMAR_PGF_ZERO);
	DMAR_LOCK(unit);
	error = dmar_load_root_entry_ptr(unit);
	if (error != 0) {
		DMAR_UNLOCK(unit);
		dmar_release_resources(dev, unit);
		return (error);
	}
	error = dmar_inv_ctx_glob(unit);
	if (error != 0) {
		DMAR_UNLOCK(unit);
		dmar_release_resources(dev, unit);
		return (error);
	}
	if ((unit->hw_ecap & DMAR_ECAP_DI) != 0) {
		error = dmar_inv_iotlb_glob(unit);
		if (error != 0) {
			DMAR_UNLOCK(unit);
			dmar_release_resources(dev, unit);
			return (error);
		}
	}

	DMAR_UNLOCK(unit);
	error = dmar_init_fault_log(unit);
	if (error != 0) {
		dmar_release_resources(dev, unit);
		return (error);
	}
	error = dmar_init_qi(unit);
	if (error != 0) {
		dmar_release_resources(dev, unit);
		return (error);
	}
	error = dmar_init_irt(unit);
	if (error != 0) {
		dmar_release_resources(dev, unit);
		return (error);
	}
	error = dmar_init_busdma(unit);
	if (error != 0) {
		dmar_release_resources(dev, unit);
		return (error);
	}

#ifdef NOTYET
	DMAR_LOCK(unit);
	error = dmar_enable_translation(unit);
	if (error != 0) {
		DMAR_UNLOCK(unit);
		dmar_release_resources(dev, unit);
		return (error);
	}
	DMAR_UNLOCK(unit);
#endif

	return (0);
}