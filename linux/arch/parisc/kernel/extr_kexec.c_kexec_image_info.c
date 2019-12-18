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
struct kimage {unsigned long nr_segments; int /*<<< orphan*/  cmdline_buf; scalar_t__ cmdline_buf_len; scalar_t__ file_mode; int /*<<< orphan*/  head; int /*<<< orphan*/  start; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  kexec_show_segment_info (struct kimage const*,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void kexec_image_info(const struct kimage *kimage)
{
	unsigned long i;

	pr_debug("kexec kimage info:\n");
	pr_debug("  type:        %d\n", kimage->type);
	pr_debug("  start:       %lx\n", kimage->start);
	pr_debug("  head:        %lx\n", kimage->head);
	pr_debug("  nr_segments: %lu\n", kimage->nr_segments);

	for (i = 0; i < kimage->nr_segments; i++)
		kexec_show_segment_info(kimage, i);

#ifdef CONFIG_KEXEC_FILE
	if (kimage->file_mode) {
		pr_debug("cmdline: %.*s\n", (int)kimage->cmdline_buf_len,
			 kimage->cmdline_buf);
	}
#endif
}