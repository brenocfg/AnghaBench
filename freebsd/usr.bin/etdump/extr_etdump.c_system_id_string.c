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
typedef  int u_char ;

/* Variables and functions */
#define  ET_SYS_EFI 131 
#define  ET_SYS_MAC 130 
#define  ET_SYS_PPC 129 
#define  ET_SYS_X86 128 

const char *
system_id_string(u_char system_id)
{

	switch (system_id) {
	case ET_SYS_X86:
		return ("i386");
	case ET_SYS_PPC:
		return ("powerpc");
	case ET_SYS_MAC:
		return ("mac");
	case ET_SYS_EFI:
		return ("efi");
	default:
		return ("invalid");
	}
}