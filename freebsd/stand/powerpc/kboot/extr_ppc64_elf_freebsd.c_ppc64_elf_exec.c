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
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct trampoline_data {void* mdp; void* dtb; void* kernel_entry; void* mdp_size; void* of_entry; void* phys_mem_offset; } ;
struct preloaded_file {int /*<<< orphan*/  f_args; } ;
struct file_metadata {int /*<<< orphan*/  md_data; } ;
struct TYPE_4__ {int (* arch_loadaddr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* arch_kexec_kseg_get ) (int*,void**) ;int /*<<< orphan*/  (* arch_copyin ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* arch_copyout ) (int,int*,int) ;} ;
struct TYPE_3__ {int e_flags; int e_entry; } ;
typedef  TYPE_1__ Elf_Ehdr ;

/* Variables and functions */
 int EFTYPE ; 
 int /*<<< orphan*/  LOAD_RAW ; 
 int /*<<< orphan*/  MODINFOMD_ELFHDR ; 
 TYPE_2__ archsw ; 
 int be32toh (void*) ; 
 int be64toh (int) ; 
 int /*<<< orphan*/  dev_cleanup () ; 
 int elf64_relocation_offset ; 
 struct file_metadata* file_findmetadata (struct preloaded_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int host_reboot (int,int,int,uintptr_t) ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  kerneltramp ; 
 int kexec_load (int,int,uintptr_t) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int md_load64 (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int*,void**) ; 
 int /*<<< orphan*/  szkerneltramp ; 

int
ppc64_elf_exec(struct preloaded_file *fp)
{
	struct file_metadata	*fmp;
	vm_offset_t		mdp, dtb;
	Elf_Ehdr		*e;
	int			error;
	uint32_t		*trampoline;
	uint64_t		entry;
	uint64_t		trampolinebase;
	struct trampoline_data	*trampoline_data;
	int			nseg;
	void			*kseg;

	if ((fmp = file_findmetadata(fp, MODINFOMD_ELFHDR)) == NULL) {
		return(EFTYPE);
	}
	e = (Elf_Ehdr *)&fmp->md_data;

	/*
	 * Figure out where to put it.
	 *
	 * Linux does not allow to do kexec_load into
	 * any part of memory. Ask arch_loadaddr to
	 * resolve the first available chunk of physical
	 * memory where loading is possible (load_addr).
	 *
	 * Memory organization is shown below.
	 * It is assumed, that text segment offset of
	 * kernel ELF (KERNPHYSADDR) is non-zero,
	 * which is true for PPC/PPC64 architectures,
	 * where default is 0x100000.
	 *
	 * load_addr:                 trampoline code
	 * load_addr + KERNPHYSADDR:  kernel text segment
	 */
	trampolinebase = archsw.arch_loadaddr(LOAD_RAW, NULL, 0);
	printf("Load address at %#jx\n", (uintmax_t)trampolinebase);
	printf("Relocation offset is %#jx\n", (uintmax_t)elf64_relocation_offset);

	/* Set up loader trampoline */
	trampoline = malloc(szkerneltramp);
	memcpy(trampoline, &kerneltramp, szkerneltramp);

	/* Parse function descriptor for ELFv1 kernels */
	if ((e->e_flags & 3) == 2)
		entry = e->e_entry;
	else {
		archsw.arch_copyout(e->e_entry + elf64_relocation_offset,
		    &entry, 8);
		entry = be64toh(entry);
	}

	/*
	 * Placeholder for trampoline data is at trampolinebase + 0x08
	 * CAUTION: all data must be Big Endian
	 */
	trampoline_data = (void*)&trampoline[2];
	trampoline_data->kernel_entry = htobe32(entry + elf64_relocation_offset);
	trampoline_data->phys_mem_offset = htobe32(0);
	trampoline_data->of_entry = htobe32(0);

	if ((error = md_load64(fp->f_args, &mdp, &dtb)) != 0)
		return (error);

	trampoline_data->dtb = htobe32(dtb);
	trampoline_data->mdp = htobe32(mdp);
	trampoline_data->mdp_size = htobe32(0xfb5d104d);

	printf("Kernel entry at %#jx (%#x) ...\n",
	    entry, be32toh(trampoline_data->kernel_entry));
	printf("DTB at %#x, mdp at %#x\n",
	    be32toh(trampoline_data->dtb), be32toh(trampoline_data->mdp));

	dev_cleanup();

	archsw.arch_copyin(trampoline, trampolinebase, szkerneltramp);
	free(trampoline);

	if (archsw.arch_kexec_kseg_get == NULL)
		panic("architecture did not provide kexec segment mapping");
	archsw.arch_kexec_kseg_get(&nseg, &kseg);

	error = kexec_load(trampolinebase, nseg, (uintptr_t)kseg);
	if (error != 0)
		panic("kexec_load returned error: %d", error);

	error = host_reboot(0xfee1dead, 672274793,
	    0x45584543 /* LINUX_REBOOT_CMD_KEXEC */, (uintptr_t)NULL);
	if (error != 0)
		panic("reboot returned error: %d", error);

	while (1) {}
}