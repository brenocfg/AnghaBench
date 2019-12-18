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
struct kimage {scalar_t__ type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int kexec_image_probe_default (struct kimage*,void*,unsigned long) ; 

int arch_kexec_kernel_image_probe(struct kimage *image, void *buf,
				  unsigned long buf_len)
{
	/* We don't support crash kernels yet. */
	if (image->type == KEXEC_TYPE_CRASH)
		return -EOPNOTSUPP;

	return kexec_image_probe_default(image, buf, buf_len);
}