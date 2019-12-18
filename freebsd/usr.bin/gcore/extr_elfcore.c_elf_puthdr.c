#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_entry_t ;
struct phdr_closure {size_t offset; TYPE_2__* phdr; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  binhdr ;
struct TYPE_8__ {int e_phoff; int e_ehsize; int e_phentsize; int e_shentsize; int e_phnum; int e_shnum; int e_shoff; int /*<<< orphan*/  e_shstrndx; int /*<<< orphan*/  e_flags; scalar_t__ e_entry; void* e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; void** e_ident; } ;
struct TYPE_7__ {size_t p_offset; size_t p_filesz; int p_align; int /*<<< orphan*/  p_flags; scalar_t__ p_memsz; scalar_t__ p_paddr; scalar_t__ p_vaddr; int /*<<< orphan*/  p_type; } ;
struct TYPE_6__ {int sh_size; int sh_info; int /*<<< orphan*/  sh_link; int /*<<< orphan*/  sh_type; } ;
typedef  TYPE_1__ Elf_Shdr ;
typedef  TYPE_2__ Elf_Phdr ;
typedef  TYPE_3__ Elf_Ehdr ;
typedef  int /*<<< orphan*/  Elf32_Size ;

/* Variables and functions */
 size_t EI_ABIVERSION ; 
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_MAG0 ; 
 size_t EI_MAG1 ; 
 size_t EI_MAG2 ; 
 size_t EI_MAG3 ; 
 size_t EI_OSABI ; 
 size_t EI_PAD ; 
 size_t EI_VERSION ; 
 void* ELFMAG0 ; 
 void* ELFMAG1 ; 
 void* ELFMAG2 ; 
 void* ELFMAG3 ; 
 void* ELFOSABI_FREEBSD ; 
 void* ELF_CLASS ; 
 void* ELF_DATA ; 
 int /*<<< orphan*/  ET_CORE ; 
 void* EV_CURRENT ; 
 int /*<<< orphan*/  PF_R ; 
 int PN_XNUM ; 
 int /*<<< orphan*/  PT_NOTE ; 
 int /*<<< orphan*/  SHN_UNDEF ; 
 int /*<<< orphan*/  SHT_NULL ; 
 int /*<<< orphan*/  cb_put_phdr ; 
 int /*<<< orphan*/  each_dumpable_segment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct phdr_closure*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int read (int,TYPE_3__*,int) ; 

__attribute__((used)) static void
elf_puthdr(int efd, pid_t pid, vm_map_entry_t map, void *hdr, size_t hdrsize,
    size_t notesz, size_t segoff, int numsegs)
{
	Elf_Ehdr *ehdr, binhdr;
	Elf_Phdr *phdr;
	Elf_Shdr *shdr;
	struct phdr_closure phc;
	ssize_t cnt;

	cnt = read(efd, &binhdr, sizeof(binhdr));
	if (cnt < 0)
		err(1, "Failed to re-read ELF header");
	else if (cnt != sizeof(binhdr))
		errx(1, "Failed to re-read ELF header");

	ehdr = (Elf_Ehdr *)hdr;

	ehdr->e_ident[EI_MAG0] = ELFMAG0;
	ehdr->e_ident[EI_MAG1] = ELFMAG1;
	ehdr->e_ident[EI_MAG2] = ELFMAG2;
	ehdr->e_ident[EI_MAG3] = ELFMAG3;
	ehdr->e_ident[EI_CLASS] = ELF_CLASS;
	ehdr->e_ident[EI_DATA] = ELF_DATA;
	ehdr->e_ident[EI_VERSION] = EV_CURRENT;
	ehdr->e_ident[EI_OSABI] = ELFOSABI_FREEBSD;
	ehdr->e_ident[EI_ABIVERSION] = 0;
	ehdr->e_ident[EI_PAD] = 0;
	ehdr->e_type = ET_CORE;
	ehdr->e_machine = binhdr.e_machine;
	ehdr->e_version = EV_CURRENT;
	ehdr->e_entry = 0;
	ehdr->e_phoff = sizeof(Elf_Ehdr);
	ehdr->e_flags = binhdr.e_flags;
	ehdr->e_ehsize = sizeof(Elf_Ehdr);
	ehdr->e_phentsize = sizeof(Elf_Phdr);
	ehdr->e_shentsize = sizeof(Elf_Shdr);
	ehdr->e_shstrndx = SHN_UNDEF;
	if (numsegs + 1 < PN_XNUM) {
		ehdr->e_phnum = numsegs + 1;
		ehdr->e_shnum = 0;
	} else {
		ehdr->e_phnum = PN_XNUM;
		ehdr->e_shnum = 1;

		ehdr->e_shoff = ehdr->e_phoff +
		    (numsegs + 1) * ehdr->e_phentsize;

		shdr = (Elf_Shdr *)((char *)hdr + ehdr->e_shoff);
		memset(shdr, 0, sizeof(*shdr));
		/*
		 * A special first section is used to hold large segment and
		 * section counts.  This was proposed by Sun Microsystems in
		 * Solaris and has been adopted by Linux; the standard ELF
		 * tools are already familiar with the technique.
		 *
		 * See table 7-7 of the Solaris "Linker and Libraries Guide"
		 * (or 12-7 depending on the version of the document) for more
		 * details.
		 */
		shdr->sh_type = SHT_NULL;
		shdr->sh_size = ehdr->e_shnum;
		shdr->sh_link = ehdr->e_shstrndx;
		shdr->sh_info = numsegs + 1;
	}

	/*
	 * Fill in the program header entries.
	 */
	phdr = (Elf_Phdr *)((char *)hdr + ehdr->e_phoff);

	/* The note segement. */
	phdr->p_type = PT_NOTE;
	phdr->p_offset = hdrsize;
	phdr->p_vaddr = 0;
	phdr->p_paddr = 0;
	phdr->p_filesz = notesz;
	phdr->p_memsz = 0;
	phdr->p_flags = PF_R;
	phdr->p_align = sizeof(Elf32_Size);
	phdr++;

	/* All the writable segments from the program. */
	phc.phdr = phdr;
	phc.offset = segoff;
	each_dumpable_segment(map, cb_put_phdr, &phc);
}