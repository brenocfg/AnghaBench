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
typedef  void* uint64_t ;
struct dumperinfo {int dummy; } ;
struct dump_pa {long pa_start; void* pa_size; } ;
typedef  int /*<<< orphan*/  phdr ;
struct TYPE_3__ {long p_vaddr; long p_paddr; void* p_filesz; int /*<<< orphan*/  p_align; void* p_memsz; int /*<<< orphan*/  p_offset; int /*<<< orphan*/  p_flags; int /*<<< orphan*/  p_type; } ;
typedef  TYPE_1__ Elf_Phdr ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PF_R ; 
 int /*<<< orphan*/  PT_LOAD ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 scalar_t__ do_minidump ; 
 int dumpsys_buf_write (struct dumperinfo*,char*,int) ; 
 int /*<<< orphan*/  fileofs ; 

__attribute__((used)) static int
cb_dumphdr(struct dump_pa *mdp, int seqnr, void *arg)
{
	struct dumperinfo *di = (struct dumperinfo*)arg;
	Elf_Phdr phdr;
	uint64_t size;
	int error;

	size = mdp->pa_size;
	bzero(&phdr, sizeof(phdr));
	phdr.p_type = PT_LOAD;
	phdr.p_flags = PF_R;			/* XXX */
	phdr.p_offset = fileofs;
#ifdef __powerpc__
	phdr.p_vaddr = (do_minidump? mdp->pa_start : ~0L);
	phdr.p_paddr = (do_minidump? ~0L : mdp->pa_start);
#else
	phdr.p_vaddr = mdp->pa_start;
	phdr.p_paddr = mdp->pa_start;
#endif
	phdr.p_filesz = size;
	phdr.p_memsz = size;
	phdr.p_align = PAGE_SIZE;

	error = dumpsys_buf_write(di, (char*)&phdr, sizeof(phdr));
	fileofs += phdr.p_filesz;
	return (error);
}