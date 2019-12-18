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
struct TYPE_2__ {unsigned long dtb_mem; void* dtb; } ;
struct kimage {TYPE_1__ arch; } ;
struct kexec_buf {unsigned long buf_min; char* buffer; unsigned long bufsz; unsigned long mem; unsigned long memsz; int top_down; scalar_t__ buf_max; scalar_t__ buf_align; struct kimage* image; } ;

/* Variables and functions */
 void* KEXEC_BUF_MEM_UNKNOWN ; 
 scalar_t__ SZ_1G ; 
 scalar_t__ SZ_2M ; 
 scalar_t__ ULONG_MAX ; 
 int create_dtb (struct kimage*,unsigned long,unsigned long,char*,void**) ; 
 unsigned long fdt_totalsize (void*) ; 
 int kexec_add_buffer (struct kexec_buf*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ round_down (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  vfree (void*) ; 

int load_other_segments(struct kimage *image,
			unsigned long kernel_load_addr,
			unsigned long kernel_size,
			char *initrd, unsigned long initrd_len,
			char *cmdline)
{
	struct kexec_buf kbuf;
	void *dtb = NULL;
	unsigned long initrd_load_addr = 0, dtb_len;
	int ret = 0;

	kbuf.image = image;
	/* not allocate anything below the kernel */
	kbuf.buf_min = kernel_load_addr + kernel_size;

	/* load initrd */
	if (initrd) {
		kbuf.buffer = initrd;
		kbuf.bufsz = initrd_len;
		kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
		kbuf.memsz = initrd_len;
		kbuf.buf_align = 0;
		/* within 1GB-aligned window of up to 32GB in size */
		kbuf.buf_max = round_down(kernel_load_addr, SZ_1G)
						+ (unsigned long)SZ_1G * 32;
		kbuf.top_down = false;

		ret = kexec_add_buffer(&kbuf);
		if (ret)
			goto out_err;
		initrd_load_addr = kbuf.mem;

		pr_debug("Loaded initrd at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
				initrd_load_addr, initrd_len, initrd_len);
	}

	/* load dtb */
	ret = create_dtb(image, initrd_load_addr, initrd_len, cmdline, &dtb);
	if (ret) {
		pr_err("Preparing for new dtb failed\n");
		goto out_err;
	}

	dtb_len = fdt_totalsize(dtb);
	kbuf.buffer = dtb;
	kbuf.bufsz = dtb_len;
	kbuf.mem = KEXEC_BUF_MEM_UNKNOWN;
	kbuf.memsz = dtb_len;
	/* not across 2MB boundary */
	kbuf.buf_align = SZ_2M;
	kbuf.buf_max = ULONG_MAX;
	kbuf.top_down = true;

	ret = kexec_add_buffer(&kbuf);
	if (ret)
		goto out_err;
	image->arch.dtb = dtb;
	image->arch.dtb_mem = kbuf.mem;

	pr_debug("Loaded dtb at 0x%lx bufsz=0x%lx memsz=0x%lx\n",
			kbuf.mem, dtb_len, dtb_len);

	return 0;

out_err:
	vfree(dtb);
	return ret;
}