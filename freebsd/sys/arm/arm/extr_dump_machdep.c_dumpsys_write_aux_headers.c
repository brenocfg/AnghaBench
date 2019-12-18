#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dumperinfo {int dummy; } ;
typedef  int /*<<< orphan*/  phdr ;
struct TYPE_3__ {int /*<<< orphan*/  p_align; scalar_t__ p_memsz; scalar_t__ p_filesz; int /*<<< orphan*/  p_paddr; int /*<<< orphan*/  p_vaddr; scalar_t__ p_offset; int /*<<< orphan*/  p_flags; int /*<<< orphan*/  p_type; } ;
typedef  TYPE_1__ Elf_Phdr ;

/* Variables and functions */
 int /*<<< orphan*/  KERNVIRTADDR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PF_R ; 
 int /*<<< orphan*/  PT_DUMP_DELTA ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int dumpsys_buf_write (struct dumperinfo*,char*,int) ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 

int
dumpsys_write_aux_headers(struct dumperinfo *di)
{
	Elf_Phdr phdr;
	int error;

	bzero(&phdr, sizeof(phdr));
	phdr.p_type = PT_DUMP_DELTA;
	phdr.p_flags = PF_R;			/* XXX */
	phdr.p_offset = 0;
	phdr.p_vaddr = KERNVIRTADDR;
	phdr.p_paddr = pmap_kextract(KERNVIRTADDR);
	phdr.p_filesz = 0;
	phdr.p_memsz = 0;
	phdr.p_align = PAGE_SIZE;

	error = dumpsys_buf_write(di, (char*)&phdr, sizeof(phdr));
	return (error);
}