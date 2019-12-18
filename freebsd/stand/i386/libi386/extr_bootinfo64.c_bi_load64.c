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
struct preloaded_file {scalar_t__ f_addr; scalar_t__ f_size; struct preloaded_file* f_next; } ;
struct i386_devdesc {int dummy; } ;
struct file_metadata {int /*<<< orphan*/  md_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MODINFOMD_ENVP ; 
 int /*<<< orphan*/  MODINFOMD_HOWTO ; 
 int /*<<< orphan*/  MODINFOMD_KERNEND ; 
 int /*<<< orphan*/  MODINFOMD_MODULEP ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  bcopy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bi_checkcpu () ; 
 scalar_t__ bi_copyenv (int) ; 
 scalar_t__ bi_copymodules64 (scalar_t__) ; 
 int bi_getboothowto (char*) ; 
 int /*<<< orphan*/  bios_addsmapdata (struct preloaded_file*) ; 
 int /*<<< orphan*/  file_addmetadata (struct preloaded_file*,int /*<<< orphan*/ ,int,int*) ; 
 struct preloaded_file* file_findfile (int /*<<< orphan*/ *,char*) ; 
 struct file_metadata* file_findmetadata (struct preloaded_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  geli_export_key_metadata (struct preloaded_file*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getrootmount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i386_fmtdev (void*) ; 
 int /*<<< orphan*/  i386_getdev (void**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 

int
bi_load64(char *args, vm_offset_t addr, vm_offset_t *modulep,
    vm_offset_t *kernendp, int add_smap)
{
    struct preloaded_file	*xp, *kfp;
    struct i386_devdesc		*rootdev;
    struct file_metadata	*md;
    uint64_t			kernend;
    uint64_t			envp;
    uint64_t			module;
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
    i386_getdev((void **)(&rootdev), rootdevname, NULL);
    if (rootdev == NULL) {		/* bad $rootdev/$currdev */
	printf("can't determine root device\n");
	return(EINVAL);
    }

    /* Try reading the /etc/fstab file to select the root device */
    getrootmount(i386_fmtdev((void *)rootdev));

    if (addr == 0) {
        /* find the last module in the chain */
        for (xp = file_findfile(NULL, NULL); xp != NULL; xp = xp->f_next) {
            if (addr < (xp->f_addr + xp->f_size))
                addr = xp->f_addr + xp->f_size;
        }
    }
    /* pad to a page boundary */
    addr = roundup(addr, PAGE_SIZE);

    /* place the metadata before anything */
    module = *modulep = addr;

    kfp = file_findfile(NULL, "elf kernel");
    if (kfp == NULL)
      kfp = file_findfile(NULL, "elf64 kernel");
    if (kfp == NULL)
	panic("can't find kernel file");
    kernend = 0;	/* fill it in later */
    file_addmetadata(kfp, MODINFOMD_HOWTO, sizeof howto, &howto);
    file_addmetadata(kfp, MODINFOMD_ENVP, sizeof envp, &envp);
    file_addmetadata(kfp, MODINFOMD_KERNEND, sizeof kernend, &kernend);
    file_addmetadata(kfp, MODINFOMD_MODULEP, sizeof module, &module);
    if (add_smap != 0)
        bios_addsmapdata(kfp);
#ifdef LOADER_GELI_SUPPORT
    geli_export_key_metadata(kfp);
#endif

    size = bi_copymodules64(0);

    /* copy our environment */
    envp = roundup(addr + size, PAGE_SIZE);
    addr = bi_copyenv(envp);

    /* set kernend */
    kernend = roundup(addr, PAGE_SIZE);
    *kernendp = kernend;

    /* patch MODINFOMD_KERNEND */
    md = file_findmetadata(kfp, MODINFOMD_KERNEND);
    bcopy(&kernend, md->md_data, sizeof kernend);

    /* patch MODINFOMD_ENVP */
    md = file_findmetadata(kfp, MODINFOMD_ENVP);
    bcopy(&envp, md->md_data, sizeof envp);

    /* copy module list and metadata */
    (void)bi_copymodules64(*modulep);

    return(0);
}