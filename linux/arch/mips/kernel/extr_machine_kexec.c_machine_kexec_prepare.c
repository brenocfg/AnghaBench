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
 int EINVAL ; 
 int _machine_kexec_prepare (struct kimage*) ; 
 int /*<<< orphan*/  kexec_image_info (struct kimage*) ; 
 int /*<<< orphan*/  kexec_nonboot_cpu_func () ; 

int
machine_kexec_prepare(struct kimage *kimage)
{
#ifdef CONFIG_SMP
	if (!kexec_nonboot_cpu_func())
		return -EINVAL;
#endif

	kexec_image_info(kimage);

	if (_machine_kexec_prepare)
		return _machine_kexec_prepare(kimage);

	return 0;
}