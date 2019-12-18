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
struct TYPE_5__ {scalar_t__ p_type; int p_flags; scalar_t__ p_vaddr; scalar_t__ p_filesz; } ;
struct TYPE_4__ {int phsize; int /*<<< orphan*/  path; void* relocbase; TYPE_2__* phdr; } ;
typedef  TYPE_1__ Obj_Entry ;
typedef  TYPE_2__ Elf_Phdr ;

/* Variables and functions */
 int PF_W ; 
 int PROT_WRITE ; 
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  _rtld_error (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int convert_prot (int) ; 
 int /*<<< orphan*/  errno ; 
 int mprotect (void*,size_t,int) ; 
 int round_page (scalar_t__) ; 
 int /*<<< orphan*/  rtld_strerror (int /*<<< orphan*/ ) ; 
 int trunc_page (scalar_t__) ; 

__attribute__((used)) static int
reloc_textrel_prot(Obj_Entry *obj, bool before)
{
	const Elf_Phdr *ph;
	void *base;
	size_t l, sz;
	int prot;

	for (l = obj->phsize / sizeof(*ph), ph = obj->phdr; l > 0;
	    l--, ph++) {
		if (ph->p_type != PT_LOAD || (ph->p_flags & PF_W) != 0)
			continue;
		base = obj->relocbase + trunc_page(ph->p_vaddr);
		sz = round_page(ph->p_vaddr + ph->p_filesz) -
		    trunc_page(ph->p_vaddr);
		prot = convert_prot(ph->p_flags) | (before ? PROT_WRITE : 0);
		if (mprotect(base, sz, prot) == -1) {
			_rtld_error("%s: Cannot write-%sable text segment: %s",
			    obj->path, before ? "en" : "dis",
			    rtld_strerror(errno));
			return (-1);
		}
	}
	return (0);
}