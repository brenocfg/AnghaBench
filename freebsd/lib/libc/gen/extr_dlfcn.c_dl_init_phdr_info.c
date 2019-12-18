#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char const* dlpi_name; unsigned int dlpi_phnum; int dlpi_tls_modid; int dlpi_adds; TYPE_2__ const* dlpi_phdr; void* dlpi_tls_data; int /*<<< orphan*/  dlpi_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  a_val; scalar_t__ a_ptr; } ;
struct TYPE_8__ {int a_type; TYPE_1__ a_un; } ;
struct TYPE_7__ {scalar_t__ p_type; scalar_t__ p_vaddr; } ;
typedef  TYPE_2__ Elf_Phdr ;
typedef  unsigned int Elf_Half ;
typedef  TYPE_3__ Elf_Auxinfo ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
#define  AT_BASE 131 
#define  AT_EXECPATH 130 
 int AT_NULL ; 
#define  AT_PHDR 129 
#define  AT_PHNUM 128 
 scalar_t__ PT_TLS ; 
 TYPE_3__* __elf_aux_vector ; 
 TYPE_4__ phdr_info ; 

__attribute__((used)) static void
dl_init_phdr_info(void)
{
	Elf_Auxinfo *auxp;
	unsigned int i;

	for (auxp = __elf_aux_vector; auxp->a_type != AT_NULL; auxp++) {
		switch (auxp->a_type) {
		case AT_BASE:
			phdr_info.dlpi_addr = (Elf_Addr)auxp->a_un.a_ptr;
			break;
		case AT_EXECPATH:
			phdr_info.dlpi_name = (const char *)auxp->a_un.a_ptr;
			break;
		case AT_PHDR:
			phdr_info.dlpi_phdr =
			    (const Elf_Phdr *)auxp->a_un.a_ptr;
			break;
		case AT_PHNUM:
			phdr_info.dlpi_phnum = (Elf_Half)auxp->a_un.a_val;
			break;
		}
	}
	for (i = 0; i < phdr_info.dlpi_phnum; i++) {
		if (phdr_info.dlpi_phdr[i].p_type == PT_TLS) {
			phdr_info.dlpi_tls_modid = 1;
			phdr_info.dlpi_tls_data =
			    (void*)phdr_info.dlpi_phdr[i].p_vaddr;
		}
	}
	phdr_info.dlpi_adds = 1;
}