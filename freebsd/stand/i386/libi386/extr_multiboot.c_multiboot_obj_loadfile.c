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
typedef  int /*<<< orphan*/  uint64_t ;
struct preloaded_file {char* f_name; scalar_t__ f_size; scalar_t__ f_addr; } ;
struct kernel_module {int dummy; } ;

/* Variables and functions */
 int EFTYPE ; 
 int EINVAL ; 
 scalar_t__ METADATA_RESV_SIZE (int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int elf64_load_modmetadata (struct preloaded_file*,scalar_t__) ; 
 int elf64_obj_loadfile (char*,int /*<<< orphan*/ ,struct preloaded_file**) ; 
 struct preloaded_file* file_findfile (int /*<<< orphan*/ *,char*) ; 
 struct preloaded_file* file_loadraw (char*,char*,int /*<<< orphan*/ ) ; 
 int num_modules (struct preloaded_file*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 

__attribute__((used)) static int
multiboot_obj_loadfile(char *filename, uint64_t dest,
    struct preloaded_file **result)
{
	struct preloaded_file	*mfp, *kfp, *rfp;
	struct kernel_module	*kmp;
	int			 error, mod_num;

	/* See if there's a multiboot kernel loaded */
	mfp = file_findfile(NULL, "elf multiboot kernel");
	if (mfp == NULL)
		return (EFTYPE);

	/*
	 * We have a multiboot kernel loaded, see if there's a FreeBSD
	 * kernel loaded also.
	 */
	kfp = file_findfile(NULL, "elf kernel");
	if (kfp == NULL) {
		/*
		 * No kernel loaded, this must be it. The kernel has to
		 * be loaded as a raw file, it will be processed by
		 * Xen and correctly loaded as an ELF file.
		 */
		rfp = file_loadraw(filename, "elf kernel", 0);
		if (rfp == NULL) {
			printf(
			"Unable to load %s as a multiboot payload kernel\n",
			filename);
			return (EINVAL);
		}

		/* Load kernel metadata... */
		setenv("kernelname", filename, 1);
		error = elf64_load_modmetadata(rfp, rfp->f_addr + rfp->f_size);
		if (error) {
			printf("Unable to load kernel %s metadata error: %d\n",
			    rfp->f_name, error);
			return (EINVAL);
		}

		/*
		 * Save space at the end of the kernel in order to place
		 * the metadata information. We do an approximation of the
		 * max metadata size, this is not optimal but it's probably
		 * the best we can do at this point. Once all modules are
		 * loaded and the size of the metadata is known this
		 * space will be recovered if not used.
		 */
		mod_num = num_modules(rfp);
		rfp->f_size = roundup(rfp->f_size, PAGE_SIZE);
		rfp->f_size += METADATA_RESV_SIZE(mod_num);
		*result = rfp;
	} else {
		/* The rest should be loaded as regular modules */
		error = elf64_obj_loadfile(filename, dest, result);
		if (error != 0) {
			printf("Unable to load %s as an object file, error: %d",
			    filename, error);
			return (error);
		}
	}

	return (0);
}