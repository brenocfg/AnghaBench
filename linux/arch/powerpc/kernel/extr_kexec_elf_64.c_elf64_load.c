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
struct kimage {int dummy; } ;
struct kexec_elf_info {void* buffer; TYPE_1__* proghdrs; } ;
struct kexec_buf {int top_down; void* mem; char* buffer; unsigned long bufsz; unsigned long memsz; void* buf_align; int /*<<< orphan*/  buf_max; int /*<<< orphan*/  buf_min; struct kimage* image; } ;
struct elfhdr {int dummy; } ;
struct TYPE_2__ {int p_offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* KEXEC_BUF_MEM_UNKNOWN ; 
 void* PAGE_SIZE ; 
 int fdt_open_into (int /*<<< orphan*/ ,void*,unsigned int) ; 
 int /*<<< orphan*/  fdt_pack (void*) ; 
 int fdt_totalsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_boot_params ; 
 int kexec_add_buffer (struct kexec_buf*) ; 
 int kexec_build_elf_info (char*,unsigned long,struct elfhdr*,struct kexec_elf_info*) ; 
 int kexec_elf_load (struct kimage*,struct elfhdr*,struct kexec_elf_info*,struct kexec_buf*,unsigned long*) ; 
 int /*<<< orphan*/  kexec_free_elf_info (struct kexec_elf_info*) ; 
 int kexec_load_purgatory (struct kimage*,struct kexec_buf*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc64_rma_size ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int setup_new_fdt (struct kimage*,void*,unsigned long,unsigned long,char*) ; 
 int setup_purgatory (struct kimage*,void const*,void*,unsigned long,unsigned long) ; 

__attribute__((used)) static void *elf64_load(struct kimage *image, char *kernel_buf,
			unsigned long kernel_len, char *initrd,
			unsigned long initrd_len, char *cmdline,
			unsigned long cmdline_len)
{
	int ret;
	unsigned int fdt_size;
	unsigned long kernel_load_addr;
	unsigned long initrd_load_addr = 0, fdt_load_addr;
	void *fdt;
	const void *slave_code;
	struct elfhdr ehdr;
	struct kexec_elf_info elf_info;
	struct kexec_buf kbuf = { .image = image, .buf_min = 0,
				  .buf_max = ppc64_rma_size };
	struct kexec_buf pbuf = { .image = image, .buf_min = 0,
				  .buf_max = ppc64_rma_size, .top_down = true,
				  .mem = KEXEC_BUF_MEM_UNKNOWN };

	ret = kexec_build_elf_info(kernel_buf, kernel_len, &ehdr, &elf_info);
	if (ret)
		goto out;

	ret = kexec_elf_load(image, &ehdr, &elf_info, &kbuf, &kernel_load_addr);
	if (ret)
		goto out;

	pr_debug("Loaded the kernel at 0x%lx\n", kernel_load_addr);

	ret = kexec_load_purgatory(image, &pbuf);
	if (ret) {
		pr_err("Loading purgatory failed.\n");
		goto out;
	}

	pr_debug("Loaded purgatory at 0x%lx\n", pbuf.mem);

	if (initrd != NULL) {
		kbuf.buffer = initrd;
		kbuf.bufsz = kbuf.memsz = initrd_len;
		kbuf.buf_align = PAGE_SIZE;
		kbuf.top_down = false;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		ret = kexec_add_buffer(&kbuf);
		if (ret)
			goto out;
		initrd_load_addr = kbuf.mem;

		pr_debug("Loaded initrd at 0x%lx\n", initrd_load_addr);
	}

	fdt_size = fdt_totalsize(initial_boot_params) * 2;
	fdt = kmalloc(fdt_size, GFP_KERNEL);
	if (!fdt) {
		pr_err("Not enough memory for the device tree.\n");
		ret = -ENOMEM;
		goto out;
	}
	ret = fdt_open_into(initial_boot_params, fdt, fdt_size);
	if (ret < 0) {
		pr_err("Error setting up the new device tree.\n");
		ret = -EINVAL;
		goto out;
	}

	ret = setup_new_fdt(image, fdt, initrd_load_addr, initrd_len, cmdline);
	if (ret)
		goto out;

	fdt_pack(fdt);

	kbuf.buffer = fdt;
	kbuf.bufsz = kbuf.memsz = fdt_size;
	kbuf.buf_align = PAGE_SIZE;
	kbuf.top_down = true;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	ret = kexec_add_buffer(&kbuf);
	if (ret)
		goto out;
	fdt_load_addr = kbuf.mem;

	pr_debug("Loaded device tree at 0x%lx\n", fdt_load_addr);

	slave_code = elf_info.buffer + elf_info.proghdrs[0].p_offset;
	ret = setup_purgatory(image, slave_code, fdt, kernel_load_addr,
			      fdt_load_addr);
	if (ret)
		pr_err("Error setting up the purgatory.\n");

out:
	kexec_free_elf_info(&elf_info);

	/* Make kimage_file_post_load_cleanup free the fdt buffer for us. */
	return ret ? ERR_PTR(ret) : fdt;
}