#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {int f_max; int host_ocr; int caps; int /*<<< orphan*/  f_min; } ;
struct sdhci_slot {int num; int version; int quirks; int caps; int caps2; int opt; int max_clk; int timeout_clk; int retune_mode; int retune_count; int timeout; int /*<<< orphan*/  card_poll_callout; int /*<<< orphan*/  mtx; int /*<<< orphan*/  retune_callout; int /*<<< orphan*/  timeout_callout; int /*<<< orphan*/  card_delayed_task; int /*<<< orphan*/  card_task; scalar_t__ bus; void* tune_data; void* tune_cmd; void* tune_req; TYPE_2__ host; } ;
typedef  scalar_t__ kobjop_t ;
typedef  TYPE_3__* kobjop_desc_t ;
typedef  TYPE_4__* kobj_t ;
struct TYPE_16__ {scalar_t__ func; } ;
typedef  TYPE_5__ kobj_method_t ;
typedef  scalar_t__ device_t ;
struct TYPE_15__ {TYPE_1__* ops; } ;
struct TYPE_14__ {TYPE_5__ deflt; } ;
struct TYPE_12__ {int /*<<< orphan*/  cls; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int ENXIO ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_CAP_BOOT_NOACC ; 
 int MMC_CAP_DRIVER_TYPE_A ; 
 int MMC_CAP_DRIVER_TYPE_C ; 
 int MMC_CAP_DRIVER_TYPE_D ; 
 int MMC_CAP_HSPEED ; 
 int MMC_CAP_MMC_DDR52 ; 
 int MMC_CAP_MMC_DDR52_180 ; 
 int MMC_CAP_MMC_ENH_STROBE ; 
 int MMC_CAP_MMC_HS200 ; 
 int MMC_CAP_MMC_HS200_180 ; 
 int MMC_CAP_MMC_HS400 ; 
 int MMC_CAP_MMC_HS400_180 ; 
 int MMC_CAP_SIGNALING_120 ; 
 int MMC_CAP_SIGNALING_180 ; 
 int MMC_CAP_SIGNALING_330 ; 
 int MMC_CAP_UHS_DDR50 ; 
 int MMC_CAP_UHS_SDR104 ; 
 int MMC_CAP_UHS_SDR12 ; 
 int MMC_CAP_UHS_SDR25 ; 
 int MMC_CAP_UHS_SDR50 ; 
 int MMC_CAP_WAIT_WHILE_BUSY ; 
 int MMC_OCR_290_300 ; 
 int MMC_OCR_300_310 ; 
 int MMC_OCR_320_330 ; 
 int MMC_OCR_330_340 ; 
 int MMC_OCR_LOW_VOLTAGE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int RD2 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int RD4 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int SDHCI_CAN_DDR50 ; 
 int SDHCI_CAN_DO_8BITBUS ; 
 int SDHCI_CAN_DO_DMA ; 
 int SDHCI_CAN_DO_HISPD ; 
 int SDHCI_CAN_DRIVE_TYPE_A ; 
 int SDHCI_CAN_DRIVE_TYPE_C ; 
 int SDHCI_CAN_DRIVE_TYPE_D ; 
 int SDHCI_CAN_MMC_HS400 ; 
 int SDHCI_CAN_SDR104 ; 
 int SDHCI_CAN_SDR50 ; 
 int SDHCI_CAN_VDD_180 ; 
 int SDHCI_CAN_VDD_300 ; 
 int SDHCI_CAN_VDD_330 ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES2 ; 
 int SDHCI_CAP_MODES_TUNING (int) ; 
 int /*<<< orphan*/  SDHCI_CARD_PRESENT_TICKS ; 
 int SDHCI_CLOCK_BASE_MASK ; 
 int SDHCI_CLOCK_BASE_SHIFT ; 
 int SDHCI_CLOCK_V3_BASE_MASK ; 
 int SDHCI_DEFAULT_MAX_FREQ ; 
 int SDHCI_HAVE_DMA ; 
 int /*<<< orphan*/  SDHCI_HOST_VERSION ; 
 int /*<<< orphan*/  SDHCI_LOCK_DESTROY (struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_LOCK_INIT (struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_MIN_FREQ (scalar_t__,struct sdhci_slot*) ; 
 int SDHCI_NON_REMOVABLE ; 
 int SDHCI_PLATFORM_TRANSFER ; 
 int SDHCI_QUIRK_ALL_SLOTS_NON_REMOVABLE ; 
 int SDHCI_QUIRK_BOOT_NOACC ; 
 int SDHCI_QUIRK_BROKEN_DMA ; 
 int SDHCI_QUIRK_BROKEN_MMC_HS200 ; 
 int SDHCI_QUIRK_BROKEN_TIMEOUT_VAL ; 
 int SDHCI_QUIRK_BROKEN_UHS_DDR50 ; 
 int SDHCI_QUIRK_CAPS_BIT63_FOR_MMC_HS400 ; 
 int SDHCI_QUIRK_DATA_TIMEOUT_1MHZ ; 
 int SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK ; 
 int SDHCI_QUIRK_FORCE_DMA ; 
 int SDHCI_QUIRK_MISSING_CAPS ; 
 int SDHCI_QUIRK_MMC_DDR52 ; 
 int SDHCI_QUIRK_MMC_HS400_IF_CAN_SDR104 ; 
 int SDHCI_QUIRK_POLL_CARD_PRESENT ; 
 int SDHCI_QUIRK_WAIT_WHILE_BUSY ; 
 int SDHCI_RETUNE_CNT_MASK ; 
 int SDHCI_RETUNE_CNT_SHIFT ; 
 int SDHCI_RETUNE_MODES_MASK ; 
 int SDHCI_RETUNE_MODES_SHIFT ; 
 int SDHCI_RETUNE_MODE_1 ; 
 int SDHCI_SDR50_NEEDS_TUNING ; 
 int SDHCI_SLOTTYPE_EMBEDDED ; 
 int SDHCI_SLOTTYPE_MASK ; 
 int SDHCI_SLOTTYPE_REMOVABLE ; 
 int SDHCI_SLOT_EMBEDDED ; 
 int SDHCI_SPEC_300 ; 
 int SDHCI_SPEC_VER_MASK ; 
 int SDHCI_SPEC_VER_SHIFT ; 
 int SDHCI_TIMEOUT_CLK_MASK ; 
 int SDHCI_TIMEOUT_CLK_SHIFT ; 
 int SDHCI_TIMEOUT_CLK_UNIT ; 
 int SDHCI_TUNE_SDR50 ; 
 int SDHCI_TUNING_SUPPORTED ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdhci_slot*) ; 
 int /*<<< orphan*/  TIMEOUT_TASK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdhci_slot*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdhci_slot*) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (scalar_t__) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (scalar_t__) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 TYPE_5__* kobj_lookup_method (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ mmcbr_retune_desc ; 
 TYPE_3__ mmcbr_switch_vccq_desc ; 
 TYPE_3__ mmcbr_tune_desc ; 
 int /*<<< orphan*/  sdhci_card_poll ; 
 int /*<<< orphan*/  sdhci_card_task ; 
 scalar_t__ sdhci_debug ; 
 int sdhci_dma_alloc (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_slot*) ; 
 scalar_t__ sdhci_generic_switch_vccq ; 
 int /*<<< orphan*/  sdhci_init (struct sdhci_slot*) ; 
 TYPE_3__ sdhci_set_uhs_timing_desc ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*,...) ; 
 int /*<<< orphan*/  taskqueue_swi_giant ; 

int
sdhci_init_slot(device_t dev, struct sdhci_slot *slot, int num)
{
	kobjop_desc_t kobj_desc;
	kobj_method_t *kobj_method;
	uint32_t caps, caps2, freq, host_caps;
	int err;

	SDHCI_LOCK_INIT(slot);

	slot->num = num;
	slot->bus = dev;

	slot->version = (RD2(slot, SDHCI_HOST_VERSION)
		>> SDHCI_SPEC_VER_SHIFT) & SDHCI_SPEC_VER_MASK;
	if (slot->quirks & SDHCI_QUIRK_MISSING_CAPS) {
		caps = slot->caps;
		caps2 = slot->caps2;
	} else {
		caps = RD4(slot, SDHCI_CAPABILITIES);
		if (slot->version >= SDHCI_SPEC_300)
			caps2 = RD4(slot, SDHCI_CAPABILITIES2);
		else
			caps2 = 0;
	}
	if (slot->version >= SDHCI_SPEC_300) {
		if ((caps & SDHCI_SLOTTYPE_MASK) != SDHCI_SLOTTYPE_REMOVABLE &&
		    (caps & SDHCI_SLOTTYPE_MASK) != SDHCI_SLOTTYPE_EMBEDDED) {
			slot_printf(slot,
			    "Driver doesn't support shared bus slots\n");
			SDHCI_LOCK_DESTROY(slot);
			return (ENXIO);
		} else if ((caps & SDHCI_SLOTTYPE_MASK) ==
		    SDHCI_SLOTTYPE_EMBEDDED) {
			slot->opt |= SDHCI_SLOT_EMBEDDED | SDHCI_NON_REMOVABLE;
		}
	}
	/* Calculate base clock frequency. */
	if (slot->version >= SDHCI_SPEC_300)
		freq = (caps & SDHCI_CLOCK_V3_BASE_MASK) >>
		    SDHCI_CLOCK_BASE_SHIFT;
	else
		freq = (caps & SDHCI_CLOCK_BASE_MASK) >>
		    SDHCI_CLOCK_BASE_SHIFT;
	if (freq != 0)
		slot->max_clk = freq * 1000000;
	/*
	 * If the frequency wasn't in the capabilities and the hardware driver
	 * hasn't already set max_clk we're probably not going to work right
	 * with an assumption, so complain about it.
	 */
	if (slot->max_clk == 0) {
		slot->max_clk = SDHCI_DEFAULT_MAX_FREQ * 1000000;
		slot_printf(slot, "Hardware doesn't specify base clock "
		    "frequency, using %dMHz as default.\n",
		    SDHCI_DEFAULT_MAX_FREQ);
	}
	/* Calculate/set timeout clock frequency. */
	if (slot->quirks & SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK) {
		slot->timeout_clk = slot->max_clk / 1000;
	} else if (slot->quirks & SDHCI_QUIRK_DATA_TIMEOUT_1MHZ) {
		slot->timeout_clk = 1000;
	} else {
		slot->timeout_clk = (caps & SDHCI_TIMEOUT_CLK_MASK) >>
		    SDHCI_TIMEOUT_CLK_SHIFT;
		if (caps & SDHCI_TIMEOUT_CLK_UNIT)
			slot->timeout_clk *= 1000;
	}
	/*
	 * If the frequency wasn't in the capabilities and the hardware driver
	 * hasn't already set timeout_clk we'll probably work okay using the
	 * max timeout, but still mention it.
	 */
	if (slot->timeout_clk == 0) {
		slot_printf(slot, "Hardware doesn't specify timeout clock "
		    "frequency, setting BROKEN_TIMEOUT quirk.\n");
		slot->quirks |= SDHCI_QUIRK_BROKEN_TIMEOUT_VAL;
	}

	slot->host.f_min = SDHCI_MIN_FREQ(slot->bus, slot);
	slot->host.f_max = slot->max_clk;
	slot->host.host_ocr = 0;
	if (caps & SDHCI_CAN_VDD_330)
	    slot->host.host_ocr |= MMC_OCR_320_330 | MMC_OCR_330_340;
	if (caps & SDHCI_CAN_VDD_300)
	    slot->host.host_ocr |= MMC_OCR_290_300 | MMC_OCR_300_310;
	/*
	 * 1.8V VDD is not supposed to be used for removable cards.  Hardware
	 * prior to v3.0 had no way to indicate embedded slots, but did
	 * sometimes support 1.8v for non-removable devices.
	 */
	if ((caps & SDHCI_CAN_VDD_180) && (slot->version < SDHCI_SPEC_300 ||
	    (slot->opt & SDHCI_SLOT_EMBEDDED)))
	    slot->host.host_ocr |= MMC_OCR_LOW_VOLTAGE;
	if (slot->host.host_ocr == 0) {
		slot_printf(slot, "Hardware doesn't report any "
		    "support voltages.\n");
	}

	host_caps = MMC_CAP_4_BIT_DATA;
	if (caps & SDHCI_CAN_DO_8BITBUS)
		host_caps |= MMC_CAP_8_BIT_DATA;
	if (caps & SDHCI_CAN_DO_HISPD)
		host_caps |= MMC_CAP_HSPEED;
	if (slot->quirks & SDHCI_QUIRK_BOOT_NOACC)
		host_caps |= MMC_CAP_BOOT_NOACC;
	if (slot->quirks & SDHCI_QUIRK_WAIT_WHILE_BUSY)
		host_caps |= MMC_CAP_WAIT_WHILE_BUSY;

	/* Determine supported UHS-I and eMMC modes. */
	if (caps2 & (SDHCI_CAN_SDR50 | SDHCI_CAN_SDR104 | SDHCI_CAN_DDR50))
		host_caps |= MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25;
	if (caps2 & SDHCI_CAN_SDR104) {
		host_caps |= MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_SDR50;
		if (!(slot->quirks & SDHCI_QUIRK_BROKEN_MMC_HS200))
			host_caps |= MMC_CAP_MMC_HS200;
	} else if (caps2 & SDHCI_CAN_SDR50)
		host_caps |= MMC_CAP_UHS_SDR50;
	if (caps2 & SDHCI_CAN_DDR50 &&
	    !(slot->quirks & SDHCI_QUIRK_BROKEN_UHS_DDR50))
		host_caps |= MMC_CAP_UHS_DDR50;
	if (slot->quirks & SDHCI_QUIRK_MMC_DDR52)
		host_caps |= MMC_CAP_MMC_DDR52;
	if (slot->quirks & SDHCI_QUIRK_CAPS_BIT63_FOR_MMC_HS400 &&
	    caps2 & SDHCI_CAN_MMC_HS400)
		host_caps |= MMC_CAP_MMC_HS400;
	if (slot->quirks & SDHCI_QUIRK_MMC_HS400_IF_CAN_SDR104 &&
	    caps2 & SDHCI_CAN_SDR104)
		host_caps |= MMC_CAP_MMC_HS400;

	/*
	 * Disable UHS-I and eMMC modes if the set_uhs_timing method is the
	 * default NULL implementation.
	 */
	kobj_desc = &sdhci_set_uhs_timing_desc;
	kobj_method = kobj_lookup_method(((kobj_t)dev)->ops->cls, NULL,
	    kobj_desc);
	if (kobj_method == &kobj_desc->deflt)
		host_caps &= ~(MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
		    MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_DDR50 | MMC_CAP_UHS_SDR104 |
		    MMC_CAP_MMC_DDR52 | MMC_CAP_MMC_HS200 | MMC_CAP_MMC_HS400);

#define	SDHCI_CAP_MODES_TUNING(caps2)					\
    (((caps2) & SDHCI_TUNE_SDR50 ? MMC_CAP_UHS_SDR50 : 0) |		\
    MMC_CAP_UHS_DDR50 | MMC_CAP_UHS_SDR104 | MMC_CAP_MMC_HS200 |	\
    MMC_CAP_MMC_HS400)

	/*
	 * Disable UHS-I and eMMC modes that require (re-)tuning if either
	 * the tune or re-tune method is the default NULL implementation.
	 */
	kobj_desc = &mmcbr_tune_desc;
	kobj_method = kobj_lookup_method(((kobj_t)dev)->ops->cls, NULL,
	    kobj_desc);
	if (kobj_method == &kobj_desc->deflt)
		goto no_tuning;
	kobj_desc = &mmcbr_retune_desc;
	kobj_method = kobj_lookup_method(((kobj_t)dev)->ops->cls, NULL,
	    kobj_desc);
	if (kobj_method == &kobj_desc->deflt) {
no_tuning:
		host_caps &= ~(SDHCI_CAP_MODES_TUNING(caps2));
	}

	/* Allocate tuning structures and determine tuning parameters. */
	if (host_caps & SDHCI_CAP_MODES_TUNING(caps2)) {
		slot->opt |= SDHCI_TUNING_SUPPORTED;
		slot->tune_req = malloc(sizeof(*slot->tune_req), M_DEVBUF,
		    M_WAITOK);
		slot->tune_cmd = malloc(sizeof(*slot->tune_cmd), M_DEVBUF,
		    M_WAITOK);
		slot->tune_data = malloc(sizeof(*slot->tune_data), M_DEVBUF,
		    M_WAITOK);
		if (caps2 & SDHCI_TUNE_SDR50)
			slot->opt |= SDHCI_SDR50_NEEDS_TUNING;
		slot->retune_mode = (caps2 & SDHCI_RETUNE_MODES_MASK) >>
		    SDHCI_RETUNE_MODES_SHIFT;
		if (slot->retune_mode == SDHCI_RETUNE_MODE_1) {
			slot->retune_count = (caps2 & SDHCI_RETUNE_CNT_MASK) >>
			    SDHCI_RETUNE_CNT_SHIFT;
			if (slot->retune_count > 0xb) {
				slot_printf(slot, "Unknown re-tuning count "
				    "%x, using 1 sec\n", slot->retune_count);
				slot->retune_count = 1;
			} else if (slot->retune_count != 0)
				slot->retune_count =
				    1 << (slot->retune_count - 1);
		}
	}

#undef SDHCI_CAP_MODES_TUNING

	/* Determine supported VCCQ signaling levels. */
	host_caps |= MMC_CAP_SIGNALING_330;
	if (host_caps & (MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
	    MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_DDR50 | MMC_CAP_UHS_SDR104 |
	    MMC_CAP_MMC_DDR52_180 | MMC_CAP_MMC_HS200_180 |
	    MMC_CAP_MMC_HS400_180))
		host_caps |= MMC_CAP_SIGNALING_120 | MMC_CAP_SIGNALING_180;

	/*
	 * Disable 1.2 V and 1.8 V signaling if the switch_vccq method is the
	 * default NULL implementation.  Disable 1.2 V support if it's the
	 * generic SDHCI implementation.
	 */
	kobj_desc = &mmcbr_switch_vccq_desc;
	kobj_method = kobj_lookup_method(((kobj_t)dev)->ops->cls, NULL,
	    kobj_desc);
	if (kobj_method == &kobj_desc->deflt)
		host_caps &= ~(MMC_CAP_SIGNALING_120 | MMC_CAP_SIGNALING_180);
	else if (kobj_method->func == (kobjop_t)sdhci_generic_switch_vccq)
		host_caps &= ~MMC_CAP_SIGNALING_120;

	/* Determine supported driver types (type B is always mandatory). */
	if (caps2 & SDHCI_CAN_DRIVE_TYPE_A)
		host_caps |= MMC_CAP_DRIVER_TYPE_A;
	if (caps2 & SDHCI_CAN_DRIVE_TYPE_C)
		host_caps |= MMC_CAP_DRIVER_TYPE_C;
	if (caps2 & SDHCI_CAN_DRIVE_TYPE_D)
		host_caps |= MMC_CAP_DRIVER_TYPE_D;
	slot->host.caps = host_caps;

	/* Decide if we have usable DMA. */
	if (caps & SDHCI_CAN_DO_DMA)
		slot->opt |= SDHCI_HAVE_DMA;

	if (slot->quirks & SDHCI_QUIRK_BROKEN_DMA)
		slot->opt &= ~SDHCI_HAVE_DMA;
	if (slot->quirks & SDHCI_QUIRK_FORCE_DMA)
		slot->opt |= SDHCI_HAVE_DMA;
	if (slot->quirks & SDHCI_QUIRK_ALL_SLOTS_NON_REMOVABLE)
		slot->opt |= SDHCI_NON_REMOVABLE;

	/*
	 * Use platform-provided transfer backend
	 * with PIO as a fallback mechanism
	 */
	if (slot->opt & SDHCI_PLATFORM_TRANSFER)
		slot->opt &= ~SDHCI_HAVE_DMA;

	if (slot->opt & SDHCI_HAVE_DMA) {
		err = sdhci_dma_alloc(slot);
		if (err != 0) {
			if (slot->opt & SDHCI_TUNING_SUPPORTED) {
				free(slot->tune_req, M_DEVBUF);
				free(slot->tune_cmd, M_DEVBUF);
				free(slot->tune_data, M_DEVBUF);
			}
			SDHCI_LOCK_DESTROY(slot);
			return (err);
		}
	}

	if (bootverbose || sdhci_debug) {
		slot_printf(slot,
		    "%uMHz%s %s VDD:%s%s%s VCCQ: 3.3V%s%s DRV: B%s%s%s %s %s\n",
		    slot->max_clk / 1000000,
		    (caps & SDHCI_CAN_DO_HISPD) ? " HS" : "",
		    (host_caps & MMC_CAP_8_BIT_DATA) ? "8bits" :
			((host_caps & MMC_CAP_4_BIT_DATA) ? "4bits" : "1bit"),
		    (caps & SDHCI_CAN_VDD_330) ? " 3.3V" : "",
		    (caps & SDHCI_CAN_VDD_300) ? " 3.0V" : "",
		    ((caps & SDHCI_CAN_VDD_180) &&
		    (slot->opt & SDHCI_SLOT_EMBEDDED)) ? " 1.8V" : "",
		    (host_caps & MMC_CAP_SIGNALING_180) ? " 1.8V" : "",
		    (host_caps & MMC_CAP_SIGNALING_120) ? " 1.2V" : "",
		    (host_caps & MMC_CAP_DRIVER_TYPE_A) ? "A" : "",
		    (host_caps & MMC_CAP_DRIVER_TYPE_C) ? "C" : "",
		    (host_caps & MMC_CAP_DRIVER_TYPE_D) ? "D" : "",
		    (slot->opt & SDHCI_HAVE_DMA) ? "DMA" : "PIO",
		    (slot->opt & SDHCI_SLOT_EMBEDDED) ? "embedded" :
		    (slot->opt & SDHCI_NON_REMOVABLE) ? "non-removable" :
		    "removable");
		if (host_caps & (MMC_CAP_MMC_DDR52 | MMC_CAP_MMC_HS200 |
		    MMC_CAP_MMC_HS400 | MMC_CAP_MMC_ENH_STROBE))
			slot_printf(slot, "eMMC:%s%s%s%s\n",
			    (host_caps & MMC_CAP_MMC_DDR52) ? " DDR52" : "",
			    (host_caps & MMC_CAP_MMC_HS200) ? " HS200" : "",
			    (host_caps & MMC_CAP_MMC_HS400) ? " HS400" : "",
			    ((host_caps &
			    (MMC_CAP_MMC_HS400 | MMC_CAP_MMC_ENH_STROBE)) ==
			    (MMC_CAP_MMC_HS400 | MMC_CAP_MMC_ENH_STROBE)) ?
			    " HS400ES" : "");
		if (host_caps & (MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
		    MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104))
			slot_printf(slot, "UHS-I:%s%s%s%s%s\n",
			    (host_caps & MMC_CAP_UHS_SDR12) ? " SDR12" : "",
			    (host_caps & MMC_CAP_UHS_SDR25) ? " SDR25" : "",
			    (host_caps & MMC_CAP_UHS_SDR50) ? " SDR50" : "",
			    (host_caps & MMC_CAP_UHS_SDR104) ? " SDR104" : "",
			    (host_caps & MMC_CAP_UHS_DDR50) ? " DDR50" : "");
		if (slot->opt & SDHCI_TUNING_SUPPORTED)
			slot_printf(slot, "Re-tuning count %d secs, mode %d\n",
			    slot->retune_count, slot->retune_mode + 1);
		sdhci_dumpregs(slot);
	}

	slot->timeout = 10;
	SYSCTL_ADD_INT(device_get_sysctl_ctx(slot->bus),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(slot->bus)), OID_AUTO,
	    "timeout", CTLFLAG_RWTUN, &slot->timeout, 0,
	    "Maximum timeout for SDHCI transfers (in secs)");
	TASK_INIT(&slot->card_task, 0, sdhci_card_task, slot);
	TIMEOUT_TASK_INIT(taskqueue_swi_giant, &slot->card_delayed_task, 0,
		sdhci_card_task, slot);
	callout_init(&slot->card_poll_callout, 1);
	callout_init_mtx(&slot->timeout_callout, &slot->mtx, 0);
	callout_init_mtx(&slot->retune_callout, &slot->mtx, 0);

	if ((slot->quirks & SDHCI_QUIRK_POLL_CARD_PRESENT) &&
	    !(slot->opt & SDHCI_NON_REMOVABLE)) {
		callout_reset(&slot->card_poll_callout,
		    SDHCI_CARD_PRESENT_TICKS, sdhci_card_poll, slot);
	}

	sdhci_init(slot);

	return (0);
}