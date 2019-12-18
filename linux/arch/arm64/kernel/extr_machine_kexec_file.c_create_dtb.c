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
struct kimage {int dummy; } ;

/* Variables and functions */
 size_t DTB_EXTRA_SPACE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int fdt_open_into (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  fdt_pack (void*) ; 
 size_t fdt_totalsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_boot_params ; 
 int setup_dtb (struct kimage*,unsigned long,unsigned long,char*,void*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (size_t) ; 

__attribute__((used)) static int create_dtb(struct kimage *image,
		      unsigned long initrd_load_addr, unsigned long initrd_len,
		      char *cmdline, void **dtb)
{
	void *buf;
	size_t buf_size;
	size_t cmdline_len;
	int ret;

	cmdline_len = cmdline ? strlen(cmdline) : 0;
	buf_size = fdt_totalsize(initial_boot_params)
			+ cmdline_len + DTB_EXTRA_SPACE;

	for (;;) {
		buf = vmalloc(buf_size);
		if (!buf)
			return -ENOMEM;

		/* duplicate a device tree blob */
		ret = fdt_open_into(initial_boot_params, buf, buf_size);
		if (ret)
			return -EINVAL;

		ret = setup_dtb(image, initrd_load_addr, initrd_len,
				cmdline, buf);
		if (ret) {
			vfree(buf);
			if (ret == -ENOMEM) {
				/* unlikely, but just in case */
				buf_size += DTB_EXTRA_SPACE;
				continue;
			} else {
				return ret;
			}
		}

		/* trim it */
		fdt_pack(buf);
		*dtb = buf;

		return 0;
	}
}