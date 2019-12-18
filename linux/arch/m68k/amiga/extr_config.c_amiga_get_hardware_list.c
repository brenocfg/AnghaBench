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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A1200_IDE ; 
 int /*<<< orphan*/  A2000_CLK ; 
 int /*<<< orphan*/  A3000_CLK ; 
 int /*<<< orphan*/  A3000_SCSI ; 
 int /*<<< orphan*/  A4000_IDE ; 
 int /*<<< orphan*/  A4000_SCSI ; 
 int /*<<< orphan*/  AGNUS_HR_NTSC ; 
 int /*<<< orphan*/  AGNUS_HR_PAL ; 
 int /*<<< orphan*/  AGNUS_NTSC ; 
 int /*<<< orphan*/  AGNUS_PAL ; 
 int /*<<< orphan*/  ALICE_NTSC ; 
 int /*<<< orphan*/  ALICE_PAL ; 
 int /*<<< orphan*/  AMBER_FF ; 
 int /*<<< orphan*/  AMIGAHW_ANNOUNCE (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ AMIGAHW_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AMI_AUDIO ; 
 int /*<<< orphan*/  AMI_BLITTER ; 
 int /*<<< orphan*/  AMI_FLOPPY ; 
 int /*<<< orphan*/  AMI_KEYBOARD ; 
 int /*<<< orphan*/  AMI_MOUSE ; 
 int /*<<< orphan*/  AMI_PARALLEL ; 
 int /*<<< orphan*/  AMI_SERIAL ; 
 int /*<<< orphan*/  AMI_VIDEO ; 
 int /*<<< orphan*/  CD_ROM ; 
 int /*<<< orphan*/  CHIP_RAM ; 
#define  CS_AGA 130 
#define  CS_ECS 129 
#define  CS_OCS 128 
 int /*<<< orphan*/  DENISE ; 
 int /*<<< orphan*/  DENISE_HR ; 
 int /*<<< orphan*/  LISA ; 
 int /*<<< orphan*/  MAGIC_REKICK ; 
 int /*<<< orphan*/  PAULA ; 
 int /*<<< orphan*/  PCMCIA ; 
 int /*<<< orphan*/  ZORRO ; 
 int /*<<< orphan*/  ZORRO3 ; 
 int amiga_chip_size ; 
 int amiga_chipset ; 
 int /*<<< orphan*/  amiga_eclock ; 
 int /*<<< orphan*/  amiga_psfreq ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int zorro_num_autocon ; 

__attribute__((used)) static void amiga_get_hardware_list(struct seq_file *m)
{
	if (AMIGAHW_PRESENT(CHIP_RAM))
		seq_printf(m, "Chip RAM:\t%ldK\n", amiga_chip_size>>10);
	seq_printf(m, "PS Freq:\t%dHz\nEClock Freq:\t%ldHz\n",
			amiga_psfreq, amiga_eclock);
	if (AMIGAHW_PRESENT(AMI_VIDEO)) {
		char *type;
		switch (amiga_chipset) {
		case CS_OCS:
			type = "OCS";
			break;
		case CS_ECS:
			type = "ECS";
			break;
		case CS_AGA:
			type = "AGA";
			break;
		default:
			type = "Old or Unknown";
			break;
		}
		seq_printf(m, "Graphics:\t%s\n", type);
	}

#define AMIGAHW_ANNOUNCE(name, str)			\
	if (AMIGAHW_PRESENT(name))			\
		seq_printf (m, "\t%s\n", str)

	seq_puts(m, "Detected hardware:\n");
	AMIGAHW_ANNOUNCE(AMI_VIDEO, "Amiga Video");
	AMIGAHW_ANNOUNCE(AMI_BLITTER, "Blitter");
	AMIGAHW_ANNOUNCE(AMBER_FF, "Amber Flicker Fixer");
	AMIGAHW_ANNOUNCE(AMI_AUDIO, "Amiga Audio");
	AMIGAHW_ANNOUNCE(AMI_FLOPPY, "Floppy Controller");
	AMIGAHW_ANNOUNCE(A3000_SCSI, "SCSI Controller WD33C93 (A3000 style)");
	AMIGAHW_ANNOUNCE(A4000_SCSI, "SCSI Controller NCR53C710 (A4000T style)");
	AMIGAHW_ANNOUNCE(A1200_IDE, "IDE Interface (A1200 style)");
	AMIGAHW_ANNOUNCE(A4000_IDE, "IDE Interface (A4000 style)");
	AMIGAHW_ANNOUNCE(CD_ROM, "Internal CD ROM drive");
	AMIGAHW_ANNOUNCE(AMI_KEYBOARD, "Keyboard");
	AMIGAHW_ANNOUNCE(AMI_MOUSE, "Mouse Port");
	AMIGAHW_ANNOUNCE(AMI_SERIAL, "Serial Port");
	AMIGAHW_ANNOUNCE(AMI_PARALLEL, "Parallel Port");
	AMIGAHW_ANNOUNCE(A2000_CLK, "Hardware Clock (A2000 style)");
	AMIGAHW_ANNOUNCE(A3000_CLK, "Hardware Clock (A3000 style)");
	AMIGAHW_ANNOUNCE(CHIP_RAM, "Chip RAM");
	AMIGAHW_ANNOUNCE(PAULA, "Paula 8364");
	AMIGAHW_ANNOUNCE(DENISE, "Denise 8362");
	AMIGAHW_ANNOUNCE(DENISE_HR, "Denise 8373");
	AMIGAHW_ANNOUNCE(LISA, "Lisa 8375");
	AMIGAHW_ANNOUNCE(AGNUS_PAL, "Normal/Fat PAL Agnus 8367/8371");
	AMIGAHW_ANNOUNCE(AGNUS_NTSC, "Normal/Fat NTSC Agnus 8361/8370");
	AMIGAHW_ANNOUNCE(AGNUS_HR_PAL, "Fat Hires PAL Agnus 8372");
	AMIGAHW_ANNOUNCE(AGNUS_HR_NTSC, "Fat Hires NTSC Agnus 8372");
	AMIGAHW_ANNOUNCE(ALICE_PAL, "PAL Alice 8374");
	AMIGAHW_ANNOUNCE(ALICE_NTSC, "NTSC Alice 8374");
	AMIGAHW_ANNOUNCE(MAGIC_REKICK, "Magic Hard Rekick");
	AMIGAHW_ANNOUNCE(PCMCIA, "PCMCIA Slot");
#ifdef CONFIG_ZORRO
	if (AMIGAHW_PRESENT(ZORRO))
		seq_printf(m, "\tZorro II%s AutoConfig: %d Expansion "
				"Device%s\n",
				AMIGAHW_PRESENT(ZORRO3) ? "I" : "",
				zorro_num_autocon, zorro_num_autocon == 1 ? "" : "s");
#endif /* CONFIG_ZORRO */

#undef AMIGAHW_ANNOUNCE
}