#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int uint32_t ;
struct preloaded_file {int /*<<< orphan*/  f_args; } ;
struct file_metadata {int /*<<< orphan*/  md_data; } ;
typedef  int /*<<< orphan*/  stack ;
struct TYPE_2__ {int e_entry; } ;
typedef  TYPE_1__ Elf_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK (int /*<<< orphan*/ ,...) ; 
 int EFTYPE ; 
 int /*<<< orphan*/  GUEST_GDT ; 
 scalar_t__ GUEST_STACK ; 
 int /*<<< orphan*/  MODINFOMD_ELFHDR ; 
 int bi_load32 (int /*<<< orphan*/ ,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  copyin ; 
 int /*<<< orphan*/  dev_cleanup () ; 
 int /*<<< orphan*/  exec ; 
 struct file_metadata* file_findmetadata (struct preloaded_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  setgdt ; 
 int /*<<< orphan*/  setreg ; 

__attribute__((used)) static int
elf32_exec(struct preloaded_file *fp)
{
	struct file_metadata	*md;
	Elf_Ehdr 		*ehdr;
	vm_offset_t		entry, bootinfop, modulep, kernend;
	int			boothowto, err, bootdev;
	uint32_t		stack[1024], *sp;


	if ((md = file_findmetadata(fp, MODINFOMD_ELFHDR)) == NULL)
		return(EFTYPE);
	ehdr = (Elf_Ehdr *)&(md->md_data);

	err = bi_load32(fp->f_args, &boothowto, &bootdev, &bootinfop, &modulep, &kernend);
	if (err != 0)
		return(err);
	entry = ehdr->e_entry & 0xffffff;

#ifdef DEBUG
	printf("Start @ 0x%lx ...\n", entry);
#endif

	dev_cleanup();

	/*
	 * Build a scratch stack at physical 0x1000
	 */
	memset(stack, 0, sizeof(stack));
	sp = (uint32_t *)((char *)stack + sizeof(stack));
	*--sp = kernend;
	*--sp = modulep;
	*--sp = bootinfop;
	*--sp = 0;
	*--sp = 0;
	*--sp = 0;
	*--sp = bootdev;
	*--sp = boothowto;

	/*
	 * Fake return address to mimic "new" boot blocks.  For more
	 * details see recover_bootinfo in locore.S.
	 */
	*--sp = 0xbeefface;
	CALLBACK(copyin, stack, GUEST_STACK, sizeof(stack));
	CALLBACK(setreg, 4, (char *)sp - (char *)stack + GUEST_STACK);

	CALLBACK(setgdt, GUEST_GDT, 8 * 4 - 1);

        CALLBACK(exec, entry);

	panic("exec returned");
}