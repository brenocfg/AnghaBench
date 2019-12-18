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

/* Variables and functions */
 int ARCH_COMMAND_LINE_SIZE ; 
 scalar_t__* COMMAND_LINE ; 
 int /*<<< orphan*/  EBCASC (scalar_t__*,int) ; 
 int /*<<< orphan*/  append_ipl_block_parm () ; 
 int /*<<< orphan*/  early_command_line ; 
 scalar_t__ has_ebcdic_char (scalar_t__*) ; 
 scalar_t__ ipl_block_valid ; 
 int /*<<< orphan*/  is_prot_virt_guest () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strim (scalar_t__*) ; 

void setup_boot_command_line(void)
{
	COMMAND_LINE[ARCH_COMMAND_LINE_SIZE - 1] = 0;
	/* convert arch command line to ascii if necessary */
	if (has_ebcdic_char(COMMAND_LINE))
		EBCASC(COMMAND_LINE, ARCH_COMMAND_LINE_SIZE);
	/* copy arch command line */
	strcpy(early_command_line, strim(COMMAND_LINE));

	/* append IPL PARM data to the boot command line */
	if (!is_prot_virt_guest() && ipl_block_valid)
		append_ipl_block_parm();
}