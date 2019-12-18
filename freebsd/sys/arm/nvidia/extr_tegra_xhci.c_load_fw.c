#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vm_size_t ;
typedef  int vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct tegra_xusb_fw_hdr {int fwimg_len; int boot_codetag; int boot_codesize; int version_id; int /*<<< orphan*/  fwimg_created_time; } ;
struct tegra_xhci_softc {int fw_size; int /*<<< orphan*/  dev; scalar_t__ fw_vaddr; int /*<<< orphan*/  fw_name; } ;
struct firmware {scalar_t__ data; } ;
struct clocktime {int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  year; int /*<<< orphan*/  mon; int /*<<< orphan*/  day; } ;

/* Variables and functions */
 int APMAP_BOOTPATH ; 
 int /*<<< orphan*/  ARU_RST_RESET ; 
 int CPUCTL_STARTCPU ; 
 int CPUCTL_STOPPED ; 
 int CSB_RD4 (struct tegra_xhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSB_WR4 (struct tegra_xhci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOENT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FIRMWARE_UNLOAD ; 
 int /*<<< orphan*/  FPCI_WR4 (struct tegra_xhci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IMFILLRNG1_TAG_HI (int) ; 
 int IMFILLRNG1_TAG_LO (int) ; 
 int L2IMEMOP_INVALIDATE_ALL ; 
 int L2IMEMOP_LOAD_LOCKED_RESULT ; 
 int L2IMEMOP_RESULT_VLD ; 
 int L2IMEMOP_SIZE_OFFSET (int) ; 
 int L2IMEMOP_SIZE_SIZE (int) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  XUSB_CFG_ARU_RST ; 
 int /*<<< orphan*/  XUSB_CSB_IMEM_BLOCK_SIZE ; 
 int /*<<< orphan*/  XUSB_CSB_MEMPOOL_APMAP ; 
 int /*<<< orphan*/  XUSB_CSB_MEMPOOL_ILOAD_ATTR ; 
 int /*<<< orphan*/  XUSB_CSB_MEMPOOL_ILOAD_BASE_HI ; 
 int /*<<< orphan*/  XUSB_CSB_MEMPOOL_ILOAD_BASE_LO ; 
 int /*<<< orphan*/  XUSB_CSB_MEMPOOL_L2IMEMOP_RESULT ; 
 int /*<<< orphan*/  XUSB_CSB_MEMPOOL_L2IMEMOP_SIZE ; 
 int /*<<< orphan*/  XUSB_CSB_MEMPOOL_L2IMEMOP_TRIG ; 
 int /*<<< orphan*/  XUSB_FALCON_BOOTVEC ; 
 int /*<<< orphan*/  XUSB_FALCON_CPUCTL ; 
 int /*<<< orphan*/  XUSB_FALCON_DMACTL ; 
 int /*<<< orphan*/  XUSB_FALCON_IMFILLCTL ; 
 int /*<<< orphan*/  XUSB_FALCON_IMFILLRNG1 ; 
 int /*<<< orphan*/  clock_ts_to_ct (struct timespec*,struct clocktime*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct firmware* firmware_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmware_put (struct firmware const*,int /*<<< orphan*/ ) ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 scalar_t__ kmem_alloc_contig (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 int vtophys (scalar_t__) ; 

__attribute__((used)) static int
load_fw(struct tegra_xhci_softc *sc)
{
	const struct firmware *fw;
	const struct tegra_xusb_fw_hdr *fw_hdr;
	vm_paddr_t fw_paddr, fw_base;
	vm_offset_t fw_vaddr;
	vm_size_t fw_size;
	uint32_t code_tags, code_size;
	struct clocktime fw_clock;
	struct timespec	fw_timespec;
	int i;

	/* Reset ARU */
	FPCI_WR4(sc, XUSB_CFG_ARU_RST, ARU_RST_RESET);
	DELAY(3000);

	/* Check if FALCON already runs */
	if (CSB_RD4(sc, XUSB_CSB_MEMPOOL_ILOAD_BASE_LO) != 0) {
		device_printf(sc->dev,
		    "XUSB CPU is already loaded, CPUCTL: 0x%08X\n",
			 CSB_RD4(sc, XUSB_FALCON_CPUCTL));
		return (0);
	}

	fw = firmware_get(sc->fw_name);
	if (fw == NULL) {
		device_printf(sc->dev, "Cannot read xusb firmware\n");
		return (ENOENT);
	}

	/* Allocate uncached memory and copy firmware into. */
	fw_hdr = (const struct tegra_xusb_fw_hdr *)fw->data;
	fw_size = fw_hdr->fwimg_len;

	fw_vaddr = kmem_alloc_contig(fw_size, M_WAITOK, 0, -1UL, PAGE_SIZE, 0,
	    VM_MEMATTR_UNCACHEABLE);
	fw_paddr = vtophys(fw_vaddr);
	fw_hdr = (const struct tegra_xusb_fw_hdr *)fw_vaddr;
	memcpy((void *)fw_vaddr, fw->data, fw_size);

	firmware_put(fw, FIRMWARE_UNLOAD);
	sc->fw_vaddr = fw_vaddr;
	sc->fw_size = fw_size;

	/* Setup firmware physical address and size. */
	fw_base = fw_paddr + sizeof(*fw_hdr);
	CSB_WR4(sc, XUSB_CSB_MEMPOOL_ILOAD_ATTR, fw_size);
	CSB_WR4(sc, XUSB_CSB_MEMPOOL_ILOAD_BASE_LO, fw_base & 0xFFFFFFFF);
	CSB_WR4(sc, XUSB_CSB_MEMPOOL_ILOAD_BASE_HI, (uint64_t)fw_base >> 32);
	CSB_WR4(sc, XUSB_CSB_MEMPOOL_APMAP, APMAP_BOOTPATH);

	/* Invalidate full L2IMEM context. */
	CSB_WR4(sc, XUSB_CSB_MEMPOOL_L2IMEMOP_TRIG,
	    L2IMEMOP_INVALIDATE_ALL);

	/* Program load of L2IMEM by boot code. */
	code_tags = howmany(fw_hdr->boot_codetag, XUSB_CSB_IMEM_BLOCK_SIZE);
	code_size = howmany(fw_hdr->boot_codesize, XUSB_CSB_IMEM_BLOCK_SIZE);
	CSB_WR4(sc, XUSB_CSB_MEMPOOL_L2IMEMOP_SIZE,
	    L2IMEMOP_SIZE_OFFSET(code_tags) |
	    L2IMEMOP_SIZE_SIZE(code_size));

	/* Execute L2IMEM boot code fetch. */
	CSB_WR4(sc, XUSB_CSB_MEMPOOL_L2IMEMOP_TRIG,
	    L2IMEMOP_LOAD_LOCKED_RESULT);

	/* Program FALCON auto-fill range and block count */
	CSB_WR4(sc, XUSB_FALCON_IMFILLCTL, code_size);
	CSB_WR4(sc, XUSB_FALCON_IMFILLRNG1,
	    IMFILLRNG1_TAG_LO(code_tags) |
	    IMFILLRNG1_TAG_HI(code_tags + code_size));

	CSB_WR4(sc, XUSB_FALCON_DMACTL, 0);
	/* Wait for CPU */
	for (i = 500; i > 0; i--) {
		if (CSB_RD4(sc, XUSB_CSB_MEMPOOL_L2IMEMOP_RESULT) &
		     L2IMEMOP_RESULT_VLD)
			break;
		DELAY(100);
	}
	if (i <= 0) {
		device_printf(sc->dev, "Timedout while wating for DMA, "
		    "state: 0x%08X\n",
		    CSB_RD4(sc, XUSB_CSB_MEMPOOL_L2IMEMOP_RESULT));
		return (ETIMEDOUT);
	}

	/* Boot FALCON cpu */
	CSB_WR4(sc, XUSB_FALCON_BOOTVEC, fw_hdr->boot_codetag);
	CSB_WR4(sc, XUSB_FALCON_CPUCTL, CPUCTL_STARTCPU);

	/* Wait for CPU */
	for (i = 50; i > 0; i--) {
		if (CSB_RD4(sc, XUSB_FALCON_CPUCTL) == CPUCTL_STOPPED)
			break;
		DELAY(100);
	}
	if (i <= 0) {
		device_printf(sc->dev, "Timedout while wating for FALCON cpu, "
		    "state: 0x%08X\n", CSB_RD4(sc, XUSB_FALCON_CPUCTL));
		return (ETIMEDOUT);
	}

	fw_timespec.tv_sec = fw_hdr->fwimg_created_time;
	fw_timespec.tv_nsec = 0;
	clock_ts_to_ct(&fw_timespec, &fw_clock);
	device_printf(sc->dev,
	    " Falcon firmware version: %02X.%02X.%04X,"
	    " (%d/%d/%d %d:%02d:%02d UTC)\n",
	    (fw_hdr->version_id >> 24) & 0xFF,(fw_hdr->version_id >> 15) & 0xFF,
	    fw_hdr->version_id & 0xFFFF,
	    fw_clock.day, fw_clock.mon, fw_clock.year,
	    fw_clock.hour, fw_clock.min, fw_clock.sec);

	return (0);
}