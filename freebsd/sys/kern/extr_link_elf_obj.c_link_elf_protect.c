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
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_3__* elf_file_t ;
struct TYPE_7__ {scalar_t__ size; } ;
struct TYPE_8__ {int nprogtab; TYPE_2__ lf; scalar_t__ address; TYPE_1__* progtab; scalar_t__ preloaded; } ;
struct TYPE_6__ {scalar_t__ size; int flags; scalar_t__ addr; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCPU_SETNAME ; 
 int SHF_EXECINSTR ; 
 int SHF_WRITE ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_RW ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  VNET_SETNAME ; 
 int /*<<< orphan*/  link_elf_protect_range (TYPE_3__*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

__attribute__((used)) static void
link_elf_protect(elf_file_t ef)
{
	vm_offset_t end, segend, segstart, start;
	vm_prot_t gapprot, prot, segprot;
	int i;

	/*
	 * If the file was preloaded, the last page may contain other preloaded
	 * data which may need to be writeable.  ELF files are always
	 * page-aligned, but other preloaded data, such as entropy or CPU
	 * microcode may be loaded with a smaller alignment.
	 */
	gapprot = ef->preloaded ? VM_PROT_RW : VM_PROT_READ;

	start = end = (vm_offset_t)ef->address;
	prot = VM_PROT_READ;
	for (i = 0; i < ef->nprogtab; i++) {
		/*
		 * VNET and DPCPU sections have their memory allocated by their
		 * respective subsystems.
		 */
		if (ef->progtab[i].name != NULL && (
#ifdef VIMAGE
		    strcmp(ef->progtab[i].name, VNET_SETNAME) == 0 ||
#endif
		    strcmp(ef->progtab[i].name, DPCPU_SETNAME) == 0))
			continue;

		segstart = trunc_page((vm_offset_t)ef->progtab[i].addr);
		segend = round_page((vm_offset_t)ef->progtab[i].addr +
		    ef->progtab[i].size);
		segprot = VM_PROT_READ;
		if ((ef->progtab[i].flags & SHF_WRITE) != 0)
			segprot |= VM_PROT_WRITE;
		if ((ef->progtab[i].flags & SHF_EXECINSTR) != 0)
			segprot |= VM_PROT_EXECUTE;

		if (end <= segstart) {
			/*
			 * Case 1: there is no overlap between the previous
			 * segment and this one.  Apply protections to the
			 * previous segment, and protect the gap between the
			 * previous and current segments, if any.
			 */
			link_elf_protect_range(ef, start, end, prot);
			link_elf_protect_range(ef, end, segstart, gapprot);

			start = segstart;
			end = segend;
			prot = segprot;
		} else if (start < segstart && end == segend) {
			/*
			 * Case 2: the current segment is a subrange of the
			 * previous segment.  Apply protections to the
			 * non-overlapping portion of the previous segment.
			 */
			link_elf_protect_range(ef, start, segstart, prot);

			start = segstart;
			prot |= segprot;
		} else if (end < segend) {
			/*
			 * Case 3: there is partial overlap between the previous
			 * and current segments.  Apply protections to the
			 * non-overlapping portion of the previous segment, and
			 * then the overlap, which must use the union of the two
			 * segments' protections.
			 */
			link_elf_protect_range(ef, start, segstart, prot);
			link_elf_protect_range(ef, segstart, end,
			    prot | segprot);
			start = end;
			end = segend;
			prot = segprot;
		} else {
			/*
			 * Case 4: the two segments reside in the same page.
			 */
			prot |= segprot;
		}
	}

	/*
	 * Fix up the last unprotected segment and trailing data.
	 */
	link_elf_protect_range(ef, start, end, prot);
	link_elf_protect_range(ef, end,
	    round_page((vm_offset_t)ef->address + ef->lf.size), gapprot);
}