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
struct linux_binprm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_32bit_task () ; 
 int map_vdso (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdso_enabled ; 
 int /*<<< orphan*/  vdso_image_32_builtin ; 
 int /*<<< orphan*/  vdso_image_64_builtin ; 
 int /*<<< orphan*/  vdso_mapping32 ; 
 int /*<<< orphan*/  vdso_mapping64 ; 

int arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
{

	if (!vdso_enabled)
		return 0;

#if defined CONFIG_COMPAT
	if (!(is_32bit_task()))
		return map_vdso(&vdso_image_64_builtin, &vdso_mapping64);
	else
		return map_vdso(&vdso_image_32_builtin, &vdso_mapping32);
#else
	return map_vdso(&vdso_image_64_builtin, &vdso_mapping64);
#endif

}