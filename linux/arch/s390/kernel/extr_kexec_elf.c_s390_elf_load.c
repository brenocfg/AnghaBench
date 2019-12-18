#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kimage {int dummy; } ;
struct TYPE_5__ {scalar_t__ e_type; scalar_t__* e_ident; size_t e_phnum; int e_phentsize; size_t e_ehsize; size_t e_phoff; } ;
struct TYPE_4__ {scalar_t__ p_type; unsigned long p_offset; size_t p_filesz; int /*<<< orphan*/  p_align; } ;
typedef  TYPE_1__ Elf_Phdr ;
typedef  TYPE_2__ Elf_Ehdr ;

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 size_t EI_CLASS ; 
 scalar_t__ ELFCLASS64 ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ ET_EXEC ; 
 scalar_t__ PT_INTERP ; 
 int /*<<< orphan*/  elf_check_arch (TYPE_2__ const*) ; 
 void* kexec_file_add_components (struct kimage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kexec_file_add_kernel_elf ; 

__attribute__((used)) static void *s390_elf_load(struct kimage *image,
			   char *kernel, unsigned long kernel_len,
			   char *initrd, unsigned long initrd_len,
			   char *cmdline, unsigned long cmdline_len)
{
	const Elf_Ehdr *ehdr;
	const Elf_Phdr *phdr;
	size_t size;
	int i;

	/* image->fobs->probe already checked for valid ELF magic number. */
	ehdr = (Elf_Ehdr *)kernel;

	if (ehdr->e_type != ET_EXEC ||
	    ehdr->e_ident[EI_CLASS] != ELFCLASS64 ||
	    !elf_check_arch(ehdr))
		return ERR_PTR(-EINVAL);

	if (!ehdr->e_phnum || ehdr->e_phentsize != sizeof(Elf_Phdr))
		return ERR_PTR(-EINVAL);

	size = ehdr->e_ehsize + ehdr->e_phoff;
	size += ehdr->e_phentsize * ehdr->e_phnum;
	if (size > kernel_len)
		return ERR_PTR(-EINVAL);

	phdr = (void *)ehdr + ehdr->e_phoff;
	size = ALIGN(size, phdr->p_align);
	for (i = 0; i < ehdr->e_phnum; i++, phdr++) {
		if (phdr->p_type == PT_INTERP)
			return ERR_PTR(-EINVAL);

		if (phdr->p_offset > kernel_len)
			return ERR_PTR(-EINVAL);

		size += ALIGN(phdr->p_filesz, phdr->p_align);
	}

	if (size > kernel_len)
		return ERR_PTR(-EINVAL);

	return kexec_file_add_components(image, kexec_file_add_kernel_elf);
}