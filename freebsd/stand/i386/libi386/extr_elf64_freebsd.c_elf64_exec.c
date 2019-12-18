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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct preloaded_file {int /*<<< orphan*/  f_args; } ;
struct file_metadata {int /*<<< orphan*/  md_data; } ;
typedef  int p4_entry_t ;
typedef  int p3_entry_t ;
struct TYPE_2__ {int e_entry; } ;
typedef  TYPE_1__ Elf_Ehdr ;

/* Variables and functions */
 int EFTYPE ; 
 int /*<<< orphan*/  MODINFOMD_ELFHDR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PG_PS ; 
 int PG_RW ; 
 int PG_U ; 
 int PG_V ; 
 int* PT2 ; 
 int* PT3 ; 
 int* PT4 ; 
 scalar_t__ VTOP (uintptr_t) ; 
 int /*<<< orphan*/  __exec (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 uintptr_t amd64_tramp ; 
 int bi_load64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_cleanup () ; 
 int entry_hi ; 
 int entry_lo ; 
 struct file_metadata* file_findmetadata (struct preloaded_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
elf64_exec(struct preloaded_file *fp)
{
    struct file_metadata	*md;
    Elf_Ehdr 			*ehdr;
    vm_offset_t			modulep, kernend;
    int				err;
    int				i;

    if ((md = file_findmetadata(fp, MODINFOMD_ELFHDR)) == NULL)
	return(EFTYPE);
    ehdr = (Elf_Ehdr *)&(md->md_data);

    err = bi_load64(fp->f_args, 0, &modulep, &kernend, 1);
    if (err != 0)
	return(err);

    bzero(PT4, PAGE_SIZE);
    bzero(PT3, PAGE_SIZE);
    bzero(PT2, PAGE_SIZE);

    /*
     * This is kinda brutal, but every single 1GB VM memory segment points to
     * the same first 1GB of physical memory.  But it is more than adequate.
     */
    for (i = 0; i < 512; i++) {
	/* Each slot of the level 4 pages points to the same level 3 page */
	PT4[i] = (p4_entry_t)VTOP((uintptr_t)&PT3[0]);
	PT4[i] |= PG_V | PG_RW | PG_U;

	/* Each slot of the level 3 pages points to the same level 2 page */
	PT3[i] = (p3_entry_t)VTOP((uintptr_t)&PT2[0]);
	PT3[i] |= PG_V | PG_RW | PG_U;

	/* The level 2 page slots are mapped with 2MB pages for 1GB. */
	PT2[i] = i * (2 * 1024 * 1024);
	PT2[i] |= PG_V | PG_RW | PG_PS | PG_U;
    }

    entry_lo = ehdr->e_entry & 0xffffffff;
    entry_hi = (ehdr->e_entry >> 32) & 0xffffffff;
#ifdef DEBUG
    printf("Start @ %#llx ...\n", ehdr->e_entry);
#endif

    dev_cleanup();
    __exec((void *)VTOP(amd64_tramp), modulep, kernend);

    panic("exec returned");
}