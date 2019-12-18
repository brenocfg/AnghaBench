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
 int ENOEXEC ; 
 unsigned long HEAD_END ; 
 int kexec_image_probe_default (struct kimage*,void*,unsigned long) ; 

int arch_kexec_kernel_image_probe(struct kimage *image, void *buf,
				  unsigned long buf_len)
{
	/* A kernel must be at least large enough to contain head.S. During
	 * load memory in head.S will be accessed, e.g. to register the next
	 * command line. If the next kernel were smaller the current kernel
	 * will panic at load.
	 */
	if (buf_len < HEAD_END)
		return -ENOEXEC;

	return kexec_image_probe_default(image, buf, buf_len);
}