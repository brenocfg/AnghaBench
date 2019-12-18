#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct fw_ohci {int quirks; int self_id_bus; int bus_time_running; int ir_context_support; int pri_req_max; int next_config_rom_bus; int config_rom_bus; TYPE_1__ card; int /*<<< orphan*/  ar_response_ctx; int /*<<< orphan*/  ar_request_ctx; scalar_t__* next_config_rom; scalar_t__ next_header; scalar_t__* config_rom; } ;
struct fw_card {int broadcast_channel_auto_allocated; int priority_budget_implemented; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ROM_SIZE ; 
 int EIO ; 
 int ENOMEM ; 
 int FW_MAX_PHYSICAL_RANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IR_CONTEXT_MULTI_CHANNEL_MODE ; 
 int /*<<< orphan*/  OHCI1394_ATRetries ; 
 int /*<<< orphan*/  OHCI1394_AsReqFilterHiSet ; 
 int /*<<< orphan*/  OHCI1394_BusOptions ; 
 int /*<<< orphan*/  OHCI1394_ConfigROMhdr ; 
 int /*<<< orphan*/  OHCI1394_ConfigROMmap ; 
 int /*<<< orphan*/  OHCI1394_FairnessControl ; 
 int /*<<< orphan*/  OHCI1394_HCControlClear ; 
 int /*<<< orphan*/  OHCI1394_HCControlSet ; 
 int OHCI1394_HCControl_BIBimageValid ; 
 int OHCI1394_HCControl_LPS ; 
 int OHCI1394_HCControl_linkEnable ; 
 int OHCI1394_HCControl_noByteSwapData ; 
 int OHCI1394_HCControl_postedWriteEnable ; 
 int /*<<< orphan*/  OHCI1394_InitialChannelsAvailableHi ; 
 int /*<<< orphan*/  OHCI1394_IntEventClear ; 
 int /*<<< orphan*/  OHCI1394_IntMaskClear ; 
 int /*<<< orphan*/  OHCI1394_IntMaskSet ; 
 int /*<<< orphan*/  OHCI1394_IsoRcvContextControlClear (int) ; 
 int /*<<< orphan*/  OHCI1394_LinkControlSet ; 
 int OHCI1394_LinkControl_cycleMaster ; 
 int OHCI1394_LinkControl_cycleTimerEnable ; 
 int OHCI1394_LinkControl_rcvPhyPkt ; 
 int OHCI1394_LinkControl_rcvSelfID ; 
 int OHCI1394_MAX_AT_REQ_RETRIES ; 
 int OHCI1394_MAX_AT_RESP_RETRIES ; 
 int OHCI1394_MAX_PHYS_RESP_RETRIES ; 
 int /*<<< orphan*/  OHCI1394_PhyUpperBound ; 
 int OHCI1394_RQPkt ; 
 int OHCI1394_RSPkt ; 
 int /*<<< orphan*/  OHCI1394_SelfIDBuffer ; 
 int /*<<< orphan*/  OHCI1394_Version ; 
 int OHCI1394_busReset ; 
 int OHCI1394_cycleInconsistent ; 
 int OHCI1394_cycleTooLong ; 
 int OHCI1394_isochRx ; 
 int OHCI1394_isochTx ; 
 int OHCI1394_masterIntEnable ; 
 int OHCI1394_postedWriteErr ; 
 int OHCI1394_regAccessFail ; 
 int OHCI1394_reqTxComplete ; 
 int OHCI1394_respTxComplete ; 
 int OHCI1394_selfIDComplete ; 
 int OHCI1394_unrecoverableError ; 
 int OHCI_PARAM_DEBUG_BUSRESETS ; 
 int OHCI_VERSION_1_1 ; 
 int PHY_CONTENDER ; 
 int PHY_LINK_ACTIVE ; 
 int QUIRK_TI_SLLZ059 ; 
 int /*<<< orphan*/  ar_context_run (int /*<<< orphan*/ *) ; 
 int be32_to_cpu (scalar_t__) ; 
 int configure_1394a_enhancements (struct fw_ohci*) ; 
 int /*<<< orphan*/  copy_config_rom (scalar_t__*,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__* dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_writes (struct fw_ohci*) ; 
 struct fw_ohci* fw_ohci (struct fw_card*) ; 
 int /*<<< orphan*/  fw_schedule_bus_reset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ohci_err (struct fw_ohci*,char*) ; 
 int /*<<< orphan*/  ohci_notice (struct fw_ohci*,char*) ; 
 int ohci_update_phy_reg (struct fw_card*,int,int /*<<< orphan*/ ,int) ; 
 int param_debug ; 
 int probe_tsb41ba3d (struct fw_ohci*) ; 
 int reg_read (struct fw_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write (struct fw_ohci*,int /*<<< orphan*/ ,int) ; 
 int software_reset (struct fw_ohci*) ; 

__attribute__((used)) static int ohci_enable(struct fw_card *card,
		       const __be32 *config_rom, size_t length)
{
	struct fw_ohci *ohci = fw_ohci(card);
	u32 lps, version, irqs;
	int i, ret;

	ret = software_reset(ohci);
	if (ret < 0) {
		ohci_err(ohci, "failed to reset ohci card\n");
		return ret;
	}

	/*
	 * Now enable LPS, which we need in order to start accessing
	 * most of the registers.  In fact, on some cards (ALI M5251),
	 * accessing registers in the SClk domain without LPS enabled
	 * will lock up the machine.  Wait 50msec to make sure we have
	 * full link enabled.  However, with some cards (well, at least
	 * a JMicron PCIe card), we have to try again sometimes.
	 *
	 * TI TSB82AA2 + TSB81BA3(A) cards signal LPS enabled early but
	 * cannot actually use the phy at that time.  These need tens of
	 * millisecods pause between LPS write and first phy access too.
	 */

	reg_write(ohci, OHCI1394_HCControlSet,
		  OHCI1394_HCControl_LPS |
		  OHCI1394_HCControl_postedWriteEnable);
	flush_writes(ohci);

	for (lps = 0, i = 0; !lps && i < 3; i++) {
		msleep(50);
		lps = reg_read(ohci, OHCI1394_HCControlSet) &
		      OHCI1394_HCControl_LPS;
	}

	if (!lps) {
		ohci_err(ohci, "failed to set Link Power Status\n");
		return -EIO;
	}

	if (ohci->quirks & QUIRK_TI_SLLZ059) {
		ret = probe_tsb41ba3d(ohci);
		if (ret < 0)
			return ret;
		if (ret)
			ohci_notice(ohci, "local TSB41BA3D phy\n");
		else
			ohci->quirks &= ~QUIRK_TI_SLLZ059;
	}

	reg_write(ohci, OHCI1394_HCControlClear,
		  OHCI1394_HCControl_noByteSwapData);

	reg_write(ohci, OHCI1394_SelfIDBuffer, ohci->self_id_bus);
	reg_write(ohci, OHCI1394_LinkControlSet,
		  OHCI1394_LinkControl_cycleTimerEnable |
		  OHCI1394_LinkControl_cycleMaster);

	reg_write(ohci, OHCI1394_ATRetries,
		  OHCI1394_MAX_AT_REQ_RETRIES |
		  (OHCI1394_MAX_AT_RESP_RETRIES << 4) |
		  (OHCI1394_MAX_PHYS_RESP_RETRIES << 8) |
		  (200 << 16));

	ohci->bus_time_running = false;

	for (i = 0; i < 32; i++)
		if (ohci->ir_context_support & (1 << i))
			reg_write(ohci, OHCI1394_IsoRcvContextControlClear(i),
				  IR_CONTEXT_MULTI_CHANNEL_MODE);

	version = reg_read(ohci, OHCI1394_Version) & 0x00ff00ff;
	if (version >= OHCI_VERSION_1_1) {
		reg_write(ohci, OHCI1394_InitialChannelsAvailableHi,
			  0xfffffffe);
		card->broadcast_channel_auto_allocated = true;
	}

	/* Get implemented bits of the priority arbitration request counter. */
	reg_write(ohci, OHCI1394_FairnessControl, 0x3f);
	ohci->pri_req_max = reg_read(ohci, OHCI1394_FairnessControl) & 0x3f;
	reg_write(ohci, OHCI1394_FairnessControl, 0);
	card->priority_budget_implemented = ohci->pri_req_max != 0;

	reg_write(ohci, OHCI1394_PhyUpperBound, FW_MAX_PHYSICAL_RANGE >> 16);
	reg_write(ohci, OHCI1394_IntEventClear, ~0);
	reg_write(ohci, OHCI1394_IntMaskClear, ~0);

	ret = configure_1394a_enhancements(ohci);
	if (ret < 0)
		return ret;

	/* Activate link_on bit and contender bit in our self ID packets.*/
	ret = ohci_update_phy_reg(card, 4, 0, PHY_LINK_ACTIVE | PHY_CONTENDER);
	if (ret < 0)
		return ret;

	/*
	 * When the link is not yet enabled, the atomic config rom
	 * update mechanism described below in ohci_set_config_rom()
	 * is not active.  We have to update ConfigRomHeader and
	 * BusOptions manually, and the write to ConfigROMmap takes
	 * effect immediately.  We tie this to the enabling of the
	 * link, so we have a valid config rom before enabling - the
	 * OHCI requires that ConfigROMhdr and BusOptions have valid
	 * values before enabling.
	 *
	 * However, when the ConfigROMmap is written, some controllers
	 * always read back quadlets 0 and 2 from the config rom to
	 * the ConfigRomHeader and BusOptions registers on bus reset.
	 * They shouldn't do that in this initial case where the link
	 * isn't enabled.  This means we have to use the same
	 * workaround here, setting the bus header to 0 and then write
	 * the right values in the bus reset tasklet.
	 */

	if (config_rom) {
		ohci->next_config_rom =
			dma_alloc_coherent(ohci->card.device, CONFIG_ROM_SIZE,
					   &ohci->next_config_rom_bus,
					   GFP_KERNEL);
		if (ohci->next_config_rom == NULL)
			return -ENOMEM;

		copy_config_rom(ohci->next_config_rom, config_rom, length);
	} else {
		/*
		 * In the suspend case, config_rom is NULL, which
		 * means that we just reuse the old config rom.
		 */
		ohci->next_config_rom = ohci->config_rom;
		ohci->next_config_rom_bus = ohci->config_rom_bus;
	}

	ohci->next_header = ohci->next_config_rom[0];
	ohci->next_config_rom[0] = 0;
	reg_write(ohci, OHCI1394_ConfigROMhdr, 0);
	reg_write(ohci, OHCI1394_BusOptions,
		  be32_to_cpu(ohci->next_config_rom[2]));
	reg_write(ohci, OHCI1394_ConfigROMmap, ohci->next_config_rom_bus);

	reg_write(ohci, OHCI1394_AsReqFilterHiSet, 0x80000000);

	irqs =	OHCI1394_reqTxComplete | OHCI1394_respTxComplete |
		OHCI1394_RQPkt | OHCI1394_RSPkt |
		OHCI1394_isochTx | OHCI1394_isochRx |
		OHCI1394_postedWriteErr |
		OHCI1394_selfIDComplete |
		OHCI1394_regAccessFail |
		OHCI1394_cycleInconsistent |
		OHCI1394_unrecoverableError |
		OHCI1394_cycleTooLong |
		OHCI1394_masterIntEnable;
	if (param_debug & OHCI_PARAM_DEBUG_BUSRESETS)
		irqs |= OHCI1394_busReset;
	reg_write(ohci, OHCI1394_IntMaskSet, irqs);

	reg_write(ohci, OHCI1394_HCControlSet,
		  OHCI1394_HCControl_linkEnable |
		  OHCI1394_HCControl_BIBimageValid);

	reg_write(ohci, OHCI1394_LinkControlSet,
		  OHCI1394_LinkControl_rcvSelfID |
		  OHCI1394_LinkControl_rcvPhyPkt);

	ar_context_run(&ohci->ar_request_ctx);
	ar_context_run(&ohci->ar_response_ctx);

	flush_writes(ohci);

	/* We are ready to go, reset bus to finish initialization. */
	fw_schedule_bus_reset(&ohci->card, false, true);

	return 0;
}