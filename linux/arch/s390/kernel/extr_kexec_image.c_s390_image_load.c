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
 void* kexec_file_add_components (struct kimage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kexec_file_add_kernel_image ; 

__attribute__((used)) static void *s390_image_load(struct kimage *image,
			     char *kernel, unsigned long kernel_len,
			     char *initrd, unsigned long initrd_len,
			     char *cmdline, unsigned long cmdline_len)
{
	return kexec_file_add_components(image, kexec_file_add_kernel_image);
}