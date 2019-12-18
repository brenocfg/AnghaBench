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
typedef  int /*<<< orphan*/  u32 ;
struct cpuinfo_x86 {char* x86_model_id; unsigned char x86_model; unsigned char x86_stepping; int x86_cache_size; int cpuid_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX86_CCR7 ; 
 char** Cx486D_name ; 
 char** Cx486S_name ; 
 char** Cx486_name ; 
 char* Cx86_cb ; 
 unsigned char Cx86_dir0_msb ; 
 int /*<<< orphan*/ * Cx86_model ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_CYRIX_5510 ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_CYRIX_5520 ; 
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_CYRIX ; 
 int /*<<< orphan*/  X86_BUG_COMA ; 
 int /*<<< orphan*/  X86_FEATURE_CXMMX ; 
 int /*<<< orphan*/  X86_FEATURE_CYRIX_ARR ; 
 int /*<<< orphan*/  X86_FEATURE_FPU ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_cx686_slop (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  clear_cpu_cap (struct cpuinfo_x86*,int) ; 
 char* cyrix_model_mult1 ; 
 char* cyrix_model_mult2 ; 
 int /*<<< orphan*/  do_cyrix_devid (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  geode_configure () ; 
 int getCx86 (int /*<<< orphan*/ ) ; 
 int isa_dma_bridge_buggy ; 
 int /*<<< orphan*/  mark_tsc_unstable (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  read_pci_config_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_cpu_bug (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_cpu_cap (struct cpuinfo_x86*,int) ; 

__attribute__((used)) static void init_cyrix(struct cpuinfo_x86 *c)
{
	unsigned char dir0, dir0_msn, dir0_lsn, dir1 = 0;
	char *buf = c->x86_model_id;
	const char *p = NULL;

	/*
	 * Bit 31 in normal CPUID used for nonstandard 3DNow ID;
	 * 3DNow is IDd by bit 31 in extended CPUID (1*32+31) anyway
	 */
	clear_cpu_cap(c, 0*32+31);

	/* Cyrix used bit 24 in extended (AMD) CPUID for Cyrix MMX extensions */
	if (test_cpu_cap(c, 1*32+24)) {
		clear_cpu_cap(c, 1*32+24);
		set_cpu_cap(c, X86_FEATURE_CXMMX);
	}

	do_cyrix_devid(&dir0, &dir1);

	check_cx686_slop(c);

	Cx86_dir0_msb = dir0_msn = dir0 >> 4; /* identifies CPU "family"   */
	dir0_lsn = dir0 & 0xf;                /* model or clock multiplier */

	/* common case step number/rev -- exceptions handled below */
	c->x86_model = (dir1 >> 4) + 1;
	c->x86_stepping = dir1 & 0xf;

	/* Now cook; the original recipe is by Channing Corn, from Cyrix.
	 * We do the same thing for each generation: we work out
	 * the model, multiplier and stepping.  Black magic included,
	 * to make the silicon step/rev numbers match the printed ones.
	 */

	switch (dir0_msn) {
		unsigned char tmp;

	case 0: /* Cx486SLC/DLC/SRx/DRx */
		p = Cx486_name[dir0_lsn & 7];
		break;

	case 1: /* Cx486S/DX/DX2/DX4 */
		p = (dir0_lsn & 8) ? Cx486D_name[dir0_lsn & 5]
			: Cx486S_name[dir0_lsn & 3];
		break;

	case 2: /* 5x86 */
		Cx86_cb[2] = cyrix_model_mult1[dir0_lsn & 5];
		p = Cx86_cb+2;
		break;

	case 3: /* 6x86/6x86L */
		Cx86_cb[1] = ' ';
		Cx86_cb[2] = cyrix_model_mult1[dir0_lsn & 5];
		if (dir1 > 0x21) { /* 686L */
			Cx86_cb[0] = 'L';
			p = Cx86_cb;
			(c->x86_model)++;
		} else             /* 686 */
			p = Cx86_cb+1;
		/* Emulate MTRRs using Cyrix's ARRs. */
		set_cpu_cap(c, X86_FEATURE_CYRIX_ARR);
		/* 6x86's contain this bug */
		set_cpu_bug(c, X86_BUG_COMA);
		break;

	case 4: /* MediaGX/GXm or Geode GXM/GXLV/GX1 */
	case 11: /* GX1 with inverted Device ID */
#ifdef CONFIG_PCI
	{
		u32 vendor, device;
		/*
		 * It isn't really a PCI quirk directly, but the cure is the
		 * same. The MediaGX has deep magic SMM stuff that handles the
		 * SB emulation. It throws away the fifo on disable_dma() which
		 * is wrong and ruins the audio.
		 *
		 *  Bug2: VSA1 has a wrap bug so that using maximum sized DMA
		 *  causes bad things. According to NatSemi VSA2 has another
		 *  bug to do with 'hlt'. I've not seen any boards using VSA2
		 *  and X doesn't seem to support it either so who cares 8).
		 *  VSA1 we work around however.
		 */

		pr_info("Working around Cyrix MediaGX virtual DMA bugs.\n");
		isa_dma_bridge_buggy = 2;

		/* We do this before the PCI layer is running. However we
		   are safe here as we know the bridge must be a Cyrix
		   companion and must be present */
		vendor = read_pci_config_16(0, 0, 0x12, PCI_VENDOR_ID);
		device = read_pci_config_16(0, 0, 0x12, PCI_DEVICE_ID);

		/*
		 *  The 5510/5520 companion chips have a funky PIT.
		 */
		if (vendor == PCI_VENDOR_ID_CYRIX &&
			(device == PCI_DEVICE_ID_CYRIX_5510 ||
					device == PCI_DEVICE_ID_CYRIX_5520))
			mark_tsc_unstable("cyrix 5510/5520 detected");
	}
#endif
		c->x86_cache_size = 16;	/* Yep 16K integrated cache thats it */

		/* GXm supports extended cpuid levels 'ala' AMD */
		if (c->cpuid_level == 2) {
			/* Enable cxMMX extensions (GX1 Datasheet 54) */
			setCx86(CX86_CCR7, getCx86(CX86_CCR7) | 1);

			/*
			 * GXm : 0x30 ... 0x5f GXm  datasheet 51
			 * GXlv: 0x6x          GXlv datasheet 54
			 *  ?  : 0x7x
			 * GX1 : 0x8x          GX1  datasheet 56
			 */
			if ((0x30 <= dir1 && dir1 <= 0x6f) ||
					(0x80 <= dir1 && dir1 <= 0x8f))
				geode_configure();
			return;
		} else { /* MediaGX */
			Cx86_cb[2] = (dir0_lsn & 1) ? '3' : '4';
			p = Cx86_cb+2;
			c->x86_model = (dir1 & 0x20) ? 1 : 2;
		}
		break;

	case 5: /* 6x86MX/M II */
		if (dir1 > 7) {
			dir0_msn++;  /* M II */
			/* Enable MMX extensions (App note 108) */
			setCx86(CX86_CCR7, getCx86(CX86_CCR7)|1);
		} else {
			/* A 6x86MX - it has the bug. */
			set_cpu_bug(c, X86_BUG_COMA);
		}
		tmp = (!(dir0_lsn & 7) || dir0_lsn & 1) ? 2 : 0;
		Cx86_cb[tmp] = cyrix_model_mult2[dir0_lsn & 7];
		p = Cx86_cb+tmp;
		if (((dir1 & 0x0f) > 4) || ((dir1 & 0xf0) == 0x20))
			(c->x86_model)++;
		/* Emulate MTRRs using Cyrix's ARRs. */
		set_cpu_cap(c, X86_FEATURE_CYRIX_ARR);
		break;

	case 0xf:  /* Cyrix 486 without DEVID registers */
		switch (dir0_lsn) {
		case 0xd:  /* either a 486SLC or DLC w/o DEVID */
			dir0_msn = 0;
			p = Cx486_name[!!boot_cpu_has(X86_FEATURE_FPU)];
			break;

		case 0xe:  /* a 486S A step */
			dir0_msn = 0;
			p = Cx486S_name[0];
			break;
		}
		break;

	default:  /* unknown (shouldn't happen, we know everyone ;-) */
		dir0_msn = 7;
		break;
	}
	strcpy(buf, Cx86_model[dir0_msn & 7]);
	if (p)
		strcat(buf, p);
	return;
}