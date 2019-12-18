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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_HOST ; 
 int /*<<< orphan*/  init_AMD_Elan_sc520 () ; 
 scalar_t__ legacy_pcib_read_config (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static const char *
legacy_pcib_is_host_bridge(int bus, int slot, int func,
			  uint32_t id, uint8_t class, uint8_t subclass,
			  uint8_t *busnum)
{
#ifdef __i386__
	const char *s = NULL;
	static uint8_t pxb[4];	/* hack for 450nx */

	*busnum = 0;

	switch (id) {
	case 0x12258086:
		s = "Intel 824?? host to PCI bridge";
		/* XXX This is a guess */
		/* *busnum = legacy_pcib_read_config(0, bus, slot, func, 0x41, 1); */
		*busnum = bus;
		break;
	case 0x71208086:
		s = "Intel 82810 (i810 GMCH) Host To Hub bridge";
		break;
	case 0x71228086:
		s = "Intel 82810-DC100 (i810-DC100 GMCH) Host To Hub bridge";
		break;
	case 0x71248086:
		s = "Intel 82810E (i810E GMCH) Host To Hub bridge";
		break;
	case 0x11308086:
		s = "Intel 82815 (i815 GMCH) Host To Hub bridge";
		break;
	case 0x71808086:
		s = "Intel 82443LX (440 LX) host to PCI bridge";
		break;
	case 0x71908086:
		s = "Intel 82443BX (440 BX) host to PCI bridge";
		break;
	case 0x71928086:
		s = "Intel 82443BX host to PCI bridge (AGP disabled)";
		break;
	case 0x71948086:
		s = "Intel 82443MX host to PCI bridge";
		break;
	case 0x71a08086:
		s = "Intel 82443GX host to PCI bridge";
		break;
	case 0x71a18086:
		s = "Intel 82443GX host to AGP bridge";
		break;
	case 0x71a28086:
		s = "Intel 82443GX host to PCI bridge (AGP disabled)";
		break;
	case 0x84c48086:
		s = "Intel 82454KX/GX (Orion) host to PCI bridge";
		*busnum = legacy_pcib_read_config(0, bus, slot, func, 0x4a, 1);
		break;
	case 0x84ca8086:
		/*
		 * For the 450nx chipset, there is a whole bundle of
		 * things pretending to be host bridges. The MIOC will
		 * be seen first and isn't really a pci bridge (the
		 * actual buses are attached to the PXB's). We need to
		 * read the registers of the MIOC to figure out the
		 * bus numbers for the PXB channels.
		 *
		 * Since the MIOC doesn't have a pci bus attached, we
		 * pretend it wasn't there.
		 */
		pxb[0] = legacy_pcib_read_config(0, bus, slot, func,
						0xd0, 1); /* BUSNO[0] */
		pxb[1] = legacy_pcib_read_config(0, bus, slot, func,
						0xd1, 1) + 1;	/* SUBA[0]+1 */
		pxb[2] = legacy_pcib_read_config(0, bus, slot, func,
						0xd3, 1); /* BUSNO[1] */
		pxb[3] = legacy_pcib_read_config(0, bus, slot, func,
						0xd4, 1) + 1;	/* SUBA[1]+1 */
		return NULL;
	case 0x84cb8086:
		switch (slot) {
		case 0x12:
			s = "Intel 82454NX PXB#0, Bus#A";
			*busnum = pxb[0];
			break;
		case 0x13:
			s = "Intel 82454NX PXB#0, Bus#B";
			*busnum = pxb[1];
			break;
		case 0x14:
			s = "Intel 82454NX PXB#1, Bus#A";
			*busnum = pxb[2];
			break;
		case 0x15:
			s = "Intel 82454NX PXB#1, Bus#B";
			*busnum = pxb[3];
			break;
		}
		break;
	case 0x1A308086:
		s = "Intel 82845 Host to PCI bridge";
		break;

		/* AMD -- vendor 0x1022 */
	case 0x30001022:
		s = "AMD Elan SC520 host to PCI bridge";
#ifdef CPU_ELAN
		init_AMD_Elan_sc520();
#else
		printf(
"*** WARNING: missing CPU_ELAN -- timekeeping may be wrong\n");
#endif
		break;
	case 0x70061022:
		s = "AMD-751 host to PCI bridge";
		break;
	case 0x700e1022:
		s = "AMD-761 host to PCI bridge";
		break;

		/* SiS -- vendor 0x1039 */
	case 0x04961039:
		s = "SiS 85c496";
		break;
	case 0x04061039:
		s = "SiS 85c501";
		break;
	case 0x06011039:
		s = "SiS 85c601";
		break;
	case 0x55911039:
		s = "SiS 5591 host to PCI bridge";
		break;
	case 0x00011039:
		s = "SiS 5591 host to AGP bridge";
		break;

		/* VLSI -- vendor 0x1004 */
	case 0x00051004:
		s = "VLSI 82C592 Host to PCI bridge";
		break;

		/* XXX Here is MVP3, I got the datasheet but NO M/B to test it  */
		/* totally. Please let me know if anything wrong.            -F */
		/* XXX need info on the MVP3 -- any takers? */
	case 0x05981106:
		s = "VIA 82C598MVP (Apollo MVP3) host bridge";
		break;

		/* AcerLabs -- vendor 0x10b9 */
		/* Funny : The datasheet told me vendor id is "10b8",sub-vendor */
		/* id is '10b9" but the register always shows "10b9". -Foxfair  */
	case 0x154110b9:
		s = "AcerLabs M1541 (Aladdin-V) PCI host bridge";
		break;

		/* OPTi -- vendor 0x1045 */
	case 0xc7011045:
		s = "OPTi 82C700 host to PCI bridge";
		break;
	case 0xc8221045:
		s = "OPTi 82C822 host to PCI Bridge";
		break;

		/* ServerWorks -- vendor 0x1166 */
	case 0x00051166:
		s = "ServerWorks NB6536 2.0HE host to PCI bridge";
		*busnum = legacy_pcib_read_config(0, bus, slot, func, 0x44, 1);
		break;

	case 0x00061166:
		/* FALLTHROUGH */
	case 0x00081166:
		/* FALLTHROUGH */
	case 0x02011166:
		/* FALLTHROUGH */
	case 0x010f1014: /* IBM re-badged ServerWorks chipset */
		s = "ServerWorks host to PCI bridge";
		*busnum = legacy_pcib_read_config(0, bus, slot, func, 0x44, 1);
		break;

	case 0x00091166:
		s = "ServerWorks NB6635 3.0LE host to PCI bridge";
		*busnum = legacy_pcib_read_config(0, bus, slot, func, 0x44, 1);
		break;

	case 0x00101166:
		s = "ServerWorks CIOB30 host to PCI bridge";
		*busnum = legacy_pcib_read_config(0, bus, slot, func, 0x44, 1);
		break;

	case 0x00111166:
		/* FALLTHROUGH */
	case 0x03021014: /* IBM re-badged ServerWorks chipset */
		s = "ServerWorks CMIC-HE host to PCI-X bridge";
		*busnum = legacy_pcib_read_config(0, bus, slot, func, 0x44, 1);
		break;

		/* XXX unknown chipset, but working */
	case 0x00171166:
		/* FALLTHROUGH */
	case 0x01011166:
	case 0x01101166:
	case 0x02251166:
		s = "ServerWorks host to PCI bridge(unknown chipset)";
		*busnum = legacy_pcib_read_config(0, bus, slot, func, 0x44, 1);
		break;

		/* Compaq/HP -- vendor 0x0e11 */
	case 0x60100e11:
		s = "Compaq/HP Model 6010 HotPlug PCI Bridge";
		*busnum = legacy_pcib_read_config(0, bus, slot, func, 0xc8, 1);
		break;

		/* Integrated Micro Solutions -- vendor 0x10e0 */
	case 0x884910e0:
		s = "Integrated Micro Solutions VL Bridge";
		break;

	default:
		if (class == PCIC_BRIDGE && subclass == PCIS_BRIDGE_HOST)
			s = "Host to PCI bridge";
		break;
	}

	return s;
#else
	const char *s = NULL;

	*busnum = 0;
	if (class == PCIC_BRIDGE && subclass == PCIS_BRIDGE_HOST)
		s = "Host to PCI bridge";
	return s;
#endif
}