#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  long uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  elf_load_addr; } ;
struct kimage {scalar_t__ type; TYPE_1__ arch; } ;
struct TYPE_4__ {long cmd_line_ptr; } ;
struct boot_params {long ext_cmd_line_ptr; TYPE_2__ hdr; } ;

/* Variables and functions */
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 unsigned long sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_cmdline(struct kimage *image, struct boot_params *params,
			 unsigned long bootparams_load_addr,
			 unsigned long cmdline_offset, char *cmdline,
			 unsigned long cmdline_len)
{
	char *cmdline_ptr = ((char *)params) + cmdline_offset;
	unsigned long cmdline_ptr_phys, len = 0;
	uint32_t cmdline_low_32, cmdline_ext_32;

	if (image->type == KEXEC_TYPE_CRASH) {
		len = sprintf(cmdline_ptr,
			"elfcorehdr=0x%lx ", image->arch.elf_load_addr);
	}
	memcpy(cmdline_ptr + len, cmdline, cmdline_len);
	cmdline_len += len;

	cmdline_ptr[cmdline_len - 1] = '\0';

	pr_debug("Final command line is: %s\n", cmdline_ptr);
	cmdline_ptr_phys = bootparams_load_addr + cmdline_offset;
	cmdline_low_32 = cmdline_ptr_phys & 0xffffffffUL;
	cmdline_ext_32 = cmdline_ptr_phys >> 32;

	params->hdr.cmd_line_ptr = cmdline_low_32;
	if (cmdline_ext_32)
		params->ext_cmd_line_ptr = cmdline_ext_32;

	return 0;
}