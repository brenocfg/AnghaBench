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
typedef  int u8 ;
struct pci_device_id {unsigned int driver_data; } ;
struct device {int dummy; } ;
struct pci_dev {int vendor; int device; int revision; struct device dev; } ;
typedef  struct ata_port_info {int flags; scalar_t__ private_data; } const ata_port_info ;
struct ata_port {int port_no; int flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  em_message_type; } ;
struct ata_host {int n_ports; struct ata_port** ports; int /*<<< orphan*/  flags; struct ahci_host_priv* private_data; } ;
struct ahci_host_priv {unsigned long flags; int cap; int port_map; int /*<<< orphan*/  em_msg_type; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_handler; int /*<<< orphan*/  mmio; } ;

/* Variables and functions */
 unsigned long AHCI_HFLAG_32BIT_ONLY ; 
 unsigned long AHCI_HFLAG_IGN_SERR_INTERNAL ; 
 unsigned long AHCI_HFLAG_NO_DEVSLP ; 
 int AHCI_HFLAG_NO_FPDMA_AA ; 
 unsigned long AHCI_HFLAG_NO_MSI ; 
 int AHCI_HFLAG_NO_SUSPEND ; 
 int AHCI_HFLAG_SRST_TOUT_IS_OFFLINE ; 
 int AHCI_MAX_CMDS ; 
 int AHCI_PCI_BAR_CAVIUM ; 
 int AHCI_PCI_BAR_CAVIUM_GEN5 ; 
 int AHCI_PCI_BAR_ENMOTUS ; 
 int AHCI_PCI_BAR_STA2X11 ; 
 int AHCI_PCI_BAR_STANDARD ; 
 int ATA_FLAG_EM ; 
 int ATA_FLAG_FPDMA_AA ; 
 int ATA_FLAG_FPDMA_AUX ; 
 int ATA_FLAG_NCQ ; 
 int ATA_FLAG_NO_LPM ; 
 int ATA_FLAG_NO_POWEROFF_SPINDOWN ; 
 int ATA_FLAG_PMP ; 
 int /*<<< orphan*/  ATA_HOST_PARALLEL_SCAN ; 
 scalar_t__ ATA_MAX_QUEUE ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HOST_CAP_64 ; 
 int HOST_CAP_NCQ ; 
 int HOST_CAP_PMP ; 
 int HOST_CAP_SSS ; 
 int /*<<< orphan*/  ICH_MAP ; 
 int PCI_VENDOR_ID_CAVIUM ; 
 int PCI_VENDOR_ID_INTEL ; 
 int PCI_VENDOR_ID_MARVELL ; 
 int PCI_VENDOR_ID_PROMISE ; 
 int PCI_VENDOR_ID_STMICRO ; 
 int /*<<< orphan*/  VPRINTK (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  acer_sa5_271_workaround (struct ahci_host_priv*,struct pci_dev*) ; 
 scalar_t__ ahci_broken_devslp (struct pci_dev*) ; 
 scalar_t__ ahci_broken_lpm (struct pci_dev*) ; 
 scalar_t__ ahci_broken_online (struct pci_dev*) ; 
 scalar_t__ ahci_broken_suspend (struct pci_dev*) ; 
 scalar_t__ ahci_broken_system_poweroff (struct pci_dev*) ; 
 int ahci_configure_dma_masks (struct pci_dev*,int) ; 
 int /*<<< orphan*/  ahci_gtf_filter_workaround (struct ata_host*) ; 
 int ahci_host_activate (struct ata_host*,int /*<<< orphan*/ *) ; 
 scalar_t__ ahci_ignore_sss ; 
 scalar_t__ ahci_init_msi (struct pci_dev*,int,struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_intel_pcs_quirk (struct pci_dev*,struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_mcp89_apple_enable (struct pci_dev*) ; 
 int /*<<< orphan*/  ahci_nr_ports (int) ; 
 int /*<<< orphan*/  ahci_p5wdh_workaround (struct ata_host*) ; 
 int /*<<< orphan*/  ahci_pci_init_controller (struct ata_host*) ; 
 int /*<<< orphan*/  ahci_pci_print_info (struct ata_host*) ; 
 int /*<<< orphan*/  ahci_pci_save_initial_config (struct pci_dev*,struct ahci_host_priv*) ; 
 struct ata_port_info const* ahci_port_info ; 
 int /*<<< orphan*/  ahci_remap_check (struct pci_dev*,int,struct ahci_host_priv*) ; 
 int ahci_reset_controller (struct ata_host*) ; 
 int /*<<< orphan*/  ahci_reset_em (struct ata_host*) ; 
 scalar_t__ ahci_sb600_enable_64bit (struct pci_dev*) ; 
 int /*<<< orphan*/  ahci_set_em_messages (struct ahci_host_priv*,struct ata_port_info const*) ; 
 int /*<<< orphan*/  ahci_sht ; 
 int /*<<< orphan*/  ahci_thunderx_irq_handler ; 
 int /*<<< orphan*/  ahci_update_initial_lpm_policy (struct ata_port*,struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ata_dummy_port_ops ; 
 struct ata_host* ata_host_alloc_pinfo (struct device*,struct ata_port_info const**,int) ; 
 int /*<<< orphan*/  ata_port_pbar_desc (struct ata_port*,int,int,char*) ; 
 int /*<<< orphan*/  ata_print_version_once (struct device*,int /*<<< orphan*/ ) ; 
 unsigned int board_ahci_mcp65 ; 
 unsigned int board_ahci_sb700 ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct ahci_host_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fls (int) ; 
 scalar_t__ is_mcp89_apple (struct pci_dev*) ; 
 int /*<<< orphan*/  marvell_enable ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_intx (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions_request_all (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  pcim_pin_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 

__attribute__((used)) static int ahci_init_one(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	unsigned int board_id = ent->driver_data;
	struct ata_port_info pi = ahci_port_info[board_id];
	const struct ata_port_info *ppi[] = { &pi, NULL };
	struct device *dev = &pdev->dev;
	struct ahci_host_priv *hpriv;
	struct ata_host *host;
	int n_ports, i, rc;
	int ahci_pci_bar = AHCI_PCI_BAR_STANDARD;

	VPRINTK("ENTER\n");

	WARN_ON((int)ATA_MAX_QUEUE > AHCI_MAX_CMDS);

	ata_print_version_once(&pdev->dev, DRV_VERSION);

	/* The AHCI driver can only drive the SATA ports, the PATA driver
	   can drive them all so if both drivers are selected make sure
	   AHCI stays out of the way */
	if (pdev->vendor == PCI_VENDOR_ID_MARVELL && !marvell_enable)
		return -ENODEV;

	/* Apple BIOS on MCP89 prevents us using AHCI */
	if (is_mcp89_apple(pdev))
		ahci_mcp89_apple_enable(pdev);

	/* Promise's PDC42819 is a SAS/SATA controller that has an AHCI mode.
	 * At the moment, we can only use the AHCI mode. Let the users know
	 * that for SAS drives they're out of luck.
	 */
	if (pdev->vendor == PCI_VENDOR_ID_PROMISE)
		dev_info(&pdev->dev,
			 "PDC42819 can only drive SATA devices with this driver\n");

	/* Some devices use non-standard BARs */
	if (pdev->vendor == PCI_VENDOR_ID_STMICRO && pdev->device == 0xCC06)
		ahci_pci_bar = AHCI_PCI_BAR_STA2X11;
	else if (pdev->vendor == 0x1c44 && pdev->device == 0x8000)
		ahci_pci_bar = AHCI_PCI_BAR_ENMOTUS;
	else if (pdev->vendor == PCI_VENDOR_ID_CAVIUM) {
		if (pdev->device == 0xa01c)
			ahci_pci_bar = AHCI_PCI_BAR_CAVIUM;
		if (pdev->device == 0xa084)
			ahci_pci_bar = AHCI_PCI_BAR_CAVIUM_GEN5;
	}

	/* acquire resources */
	rc = pcim_enable_device(pdev);
	if (rc)
		return rc;

	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
	    (pdev->device == 0x2652 || pdev->device == 0x2653)) {
		u8 map;

		/* ICH6s share the same PCI ID for both piix and ahci
		 * modes.  Enabling ahci mode while MAP indicates
		 * combined mode is a bad idea.  Yield to ata_piix.
		 */
		pci_read_config_byte(pdev, ICH_MAP, &map);
		if (map & 0x3) {
			dev_info(&pdev->dev,
				 "controller is in combined mode, can't enable AHCI mode\n");
			return -ENODEV;
		}
	}

	/* AHCI controllers often implement SFF compatible interface.
	 * Grab all PCI BARs just in case.
	 */
	rc = pcim_iomap_regions_request_all(pdev, 1 << ahci_pci_bar, DRV_NAME);
	if (rc == -EBUSY)
		pcim_pin_device(pdev);
	if (rc)
		return rc;

	hpriv = devm_kzalloc(dev, sizeof(*hpriv), GFP_KERNEL);
	if (!hpriv)
		return -ENOMEM;
	hpriv->flags |= (unsigned long)pi.private_data;

	/* MCP65 revision A1 and A2 can't do MSI */
	if (board_id == board_ahci_mcp65 &&
	    (pdev->revision == 0xa1 || pdev->revision == 0xa2))
		hpriv->flags |= AHCI_HFLAG_NO_MSI;

	/* SB800 does NOT need the workaround to ignore SERR_INTERNAL */
	if (board_id == board_ahci_sb700 && pdev->revision >= 0x40)
		hpriv->flags &= ~AHCI_HFLAG_IGN_SERR_INTERNAL;

	/* only some SB600s can do 64bit DMA */
	if (ahci_sb600_enable_64bit(pdev))
		hpriv->flags &= ~AHCI_HFLAG_32BIT_ONLY;

	hpriv->mmio = pcim_iomap_table(pdev)[ahci_pci_bar];

	/* detect remapped nvme devices */
	ahci_remap_check(pdev, ahci_pci_bar, hpriv);

	/* must set flag prior to save config in order to take effect */
	if (ahci_broken_devslp(pdev))
		hpriv->flags |= AHCI_HFLAG_NO_DEVSLP;

#ifdef CONFIG_ARM64
	if (pdev->vendor == 0x177d && pdev->device == 0xa01c)
		hpriv->irq_handler = ahci_thunderx_irq_handler;
#endif

	/* save initial config */
	ahci_pci_save_initial_config(pdev, hpriv);

	/*
	 * If platform firmware failed to enable ports, try to enable
	 * them here.
	 */
	ahci_intel_pcs_quirk(pdev, hpriv);

	/* prepare host */
	if (hpriv->cap & HOST_CAP_NCQ) {
		pi.flags |= ATA_FLAG_NCQ;
		/*
		 * Auto-activate optimization is supposed to be
		 * supported on all AHCI controllers indicating NCQ
		 * capability, but it seems to be broken on some
		 * chipsets including NVIDIAs.
		 */
		if (!(hpriv->flags & AHCI_HFLAG_NO_FPDMA_AA))
			pi.flags |= ATA_FLAG_FPDMA_AA;

		/*
		 * All AHCI controllers should be forward-compatible
		 * with the new auxiliary field. This code should be
		 * conditionalized if any buggy AHCI controllers are
		 * encountered.
		 */
		pi.flags |= ATA_FLAG_FPDMA_AUX;
	}

	if (hpriv->cap & HOST_CAP_PMP)
		pi.flags |= ATA_FLAG_PMP;

	ahci_set_em_messages(hpriv, &pi);

	if (ahci_broken_system_poweroff(pdev)) {
		pi.flags |= ATA_FLAG_NO_POWEROFF_SPINDOWN;
		dev_info(&pdev->dev,
			"quirky BIOS, skipping spindown on poweroff\n");
	}

	if (ahci_broken_lpm(pdev)) {
		pi.flags |= ATA_FLAG_NO_LPM;
		dev_warn(&pdev->dev,
			 "BIOS update required for Link Power Management support\n");
	}

	if (ahci_broken_suspend(pdev)) {
		hpriv->flags |= AHCI_HFLAG_NO_SUSPEND;
		dev_warn(&pdev->dev,
			 "BIOS update required for suspend/resume\n");
	}

	if (ahci_broken_online(pdev)) {
		hpriv->flags |= AHCI_HFLAG_SRST_TOUT_IS_OFFLINE;
		dev_info(&pdev->dev,
			 "online status unreliable, applying workaround\n");
	}


	/* Acer SA5-271 workaround modifies private_data */
	acer_sa5_271_workaround(hpriv, pdev);

	/* CAP.NP sometimes indicate the index of the last enabled
	 * port, at other times, that of the last possible port, so
	 * determining the maximum port number requires looking at
	 * both CAP.NP and port_map.
	 */
	n_ports = max(ahci_nr_ports(hpriv->cap), fls(hpriv->port_map));

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	if (!host)
		return -ENOMEM;
	host->private_data = hpriv;

	if (ahci_init_msi(pdev, n_ports, hpriv) < 0) {
		/* legacy intx interrupts */
		pci_intx(pdev, 1);
	}
	hpriv->irq = pci_irq_vector(pdev, 0);

	if (!(hpriv->cap & HOST_CAP_SSS) || ahci_ignore_sss)
		host->flags |= ATA_HOST_PARALLEL_SCAN;
	else
		dev_info(&pdev->dev, "SSS flag set, parallel bus scan disabled\n");

	if (pi.flags & ATA_FLAG_EM)
		ahci_reset_em(host);

	for (i = 0; i < host->n_ports; i++) {
		struct ata_port *ap = host->ports[i];

		ata_port_pbar_desc(ap, ahci_pci_bar, -1, "abar");
		ata_port_pbar_desc(ap, ahci_pci_bar,
				   0x100 + ap->port_no * 0x80, "port");

		/* set enclosure management message type */
		if (ap->flags & ATA_FLAG_EM)
			ap->em_message_type = hpriv->em_msg_type;

		ahci_update_initial_lpm_policy(ap, hpriv);

		/* disabled/not-implemented port */
		if (!(hpriv->port_map & (1 << i)))
			ap->ops = &ata_dummy_port_ops;
	}

	/* apply workaround for ASUS P5W DH Deluxe mainboard */
	ahci_p5wdh_workaround(host);

	/* apply gtf filter quirk */
	ahci_gtf_filter_workaround(host);

	/* initialize adapter */
	rc = ahci_configure_dma_masks(pdev, hpriv->cap & HOST_CAP_64);
	if (rc)
		return rc;

	rc = ahci_reset_controller(host);
	if (rc)
		return rc;

	ahci_pci_init_controller(host);
	ahci_pci_print_info(host);

	pci_set_master(pdev);

	rc = ahci_host_activate(host, &ahci_sht);
	if (rc)
		return rc;

	pm_runtime_put_noidle(&pdev->dev);
	return 0;
}