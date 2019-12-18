#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int uint64_t ;
struct userboot_devdesc {int dummy; } ;
struct preloaded_file {scalar_t__ f_addr; scalar_t__ f_size; struct preloaded_file* f_next; } ;
struct file_metadata {int /*<<< orphan*/  md_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MODINFOMD_ENVP ; 
 int /*<<< orphan*/  MODINFOMD_HOWTO ; 
 int /*<<< orphan*/  MODINFOMD_KERNEND ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bcopy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bi_checkcpu () ; 
 scalar_t__ bi_copyenv (scalar_t__) ; 
 scalar_t__ bi_copymodules64 (scalar_t__) ; 
 int bi_getboothowto (char*) ; 
 int /*<<< orphan*/  bios_addsmapdata (struct preloaded_file*) ; 
 int /*<<< orphan*/  file_addmetadata (struct preloaded_file*,int /*<<< orphan*/ ,int,int*) ; 
 struct preloaded_file* file_findfile (int /*<<< orphan*/ *,char*) ; 
 struct file_metadata* file_findmetadata (struct preloaded_file*,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getrootmount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  userboot_fmtdev (void*) ; 
 int /*<<< orphan*/  userboot_getdev (void**,char*,int /*<<< orphan*/ *) ; 

int
bi_load64(char *args, vm_offset_t *modulep, vm_offset_t *kernendp)
{
    struct preloaded_file	*xp, *kfp;
    struct userboot_devdesc	*rootdev;
    struct file_metadata	*md;
    vm_offset_t			addr;
    uint64_t			kernend;
    uint64_t			envp;
    vm_offset_t			size;
    char			*rootdevname;
    int				howto;

    if (!bi_checkcpu()) {
	printf("CPU doesn't support long mode\n");
	return (EINVAL);
    }

    howto = bi_getboothowto(args);

    /* 
     * Allow the environment variable 'rootdev' to override the supplied device 
     * This should perhaps go to MI code and/or have $rootdev tested/set by
     * MI code before launching the kernel.
     */
    rootdevname = getenv("rootdev");
    userboot_getdev((void **)(&rootdev), rootdevname, NULL);
    if (rootdev == NULL) {		/* bad $rootdev/$currdev */
	printf("can't determine root device\n");
	return(EINVAL);
    }

    /* Try reading the /etc/fstab file to select the root device */
    getrootmount(userboot_fmtdev((void *)rootdev));

    /* find the last module in the chain */
    addr = 0;
    for (xp = file_findfile(NULL, NULL); xp != NULL; xp = xp->f_next) {
	if (addr < (xp->f_addr + xp->f_size))
	    addr = xp->f_addr + xp->f_size;
    }
    /* pad to a page boundary */
    addr = roundup(addr, PAGE_SIZE);

    /* copy our environment */
    envp = addr;
    addr = bi_copyenv(addr);

    /* pad to a page boundary */
    addr = roundup(addr, PAGE_SIZE);

    kfp = file_findfile(NULL, "elf kernel");
    if (kfp == NULL)
      kfp = file_findfile(NULL, "elf64 kernel");
    if (kfp == NULL)
	panic("can't find kernel file");
    kernend = 0;	/* fill it in later */
    file_addmetadata(kfp, MODINFOMD_HOWTO, sizeof howto, &howto);
    file_addmetadata(kfp, MODINFOMD_ENVP, sizeof envp, &envp);
    file_addmetadata(kfp, MODINFOMD_KERNEND, sizeof kernend, &kernend);
    bios_addsmapdata(kfp);

    /* Figure out the size and location of the metadata */
    *modulep = addr;
    size = bi_copymodules64(0);
    kernend = roundup(addr + size, PAGE_SIZE);
    *kernendp = kernend;

    /* patch MODINFOMD_KERNEND */
    md = file_findmetadata(kfp, MODINFOMD_KERNEND);
    bcopy(&kernend, md->md_data, sizeof kernend);

    /* copy module list and metadata */
    (void)bi_copymodules64(addr);

    return(0);
}