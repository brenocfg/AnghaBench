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
struct kimage {unsigned long nr_segments; TYPE_1__* segment; int /*<<< orphan*/  head; int /*<<< orphan*/  start; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ memsz; scalar_t__ mem; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void kexec_image_info(const struct kimage *kimage)
{
	unsigned long i;

	pr_debug("kexec kimage info:\n");
	pr_debug("  type:        %d\n", kimage->type);
	pr_debug("  start:       %lx\n", kimage->start);
	pr_debug("  head:        %lx\n", kimage->head);
	pr_debug("  nr_segments: %lu\n", kimage->nr_segments);

	for (i = 0; i < kimage->nr_segments; i++) {
		pr_debug("    segment[%lu]: %016lx - %016lx, 0x%lx bytes, %lu pages\n",
			i,
			kimage->segment[i].mem,
			kimage->segment[i].mem + kimage->segment[i].memsz,
			(unsigned long)kimage->segment[i].memsz,
			(unsigned long)kimage->segment[i].memsz /  PAGE_SIZE);
	}
}