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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct preloaded_file {char* f_args; } ;
struct file_metadata {int /*<<< orphan*/  md_data; } ;
struct TYPE_2__ {int e_flags; scalar_t__ e_entry; } ;
typedef  TYPE_1__ Elf_Ehdr ;

/* Variables and functions */
 int EFTYPE ; 
 int /*<<< orphan*/  MODINFOMD_ELFHDR ; 
 int /*<<< orphan*/  dev_cleanup () ; 
 struct file_metadata* file_findmetadata (struct preloaded_file*,int /*<<< orphan*/ ) ; 
 int md_load64 (char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 void stub1 (void*) ; 

int
ppc64_uboot_elf_exec(struct preloaded_file *fp)
{
	struct file_metadata	*fmp;
	vm_offset_t		mdp, dtbp;
	Elf_Ehdr		*e;
	int			error;
	void			(*entry)(void *);

	if ((fmp = file_findmetadata(fp, MODINFOMD_ELFHDR)) == NULL) {
		return(EFTYPE);
	}
	e = (Elf_Ehdr *)&fmp->md_data;
	
	/* Handle function descriptor for ELFv1 kernels */
	if ((e->e_flags & 3) == 2)
		entry = (void (*)(void*))(intptr_t)e->e_entry;
	else
		entry = *(void (*)(void*))(uint64_t *)(intptr_t)e->e_entry;

	if ((error = md_load64(fp->f_args, &mdp, &dtbp)) != 0)
		return (error);

	dev_cleanup();
	printf("Kernel args: %s\n", fp->f_args);

	(*entry)((void *)mdp);
	panic("exec returned");
}