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
struct vdso_elfinfo {int dummy; } ;

/* Variables and functions */
 int patchsym32 (struct vdso_elfinfo*,char const*,char const*) ; 
 int patchsym64 (struct vdso_elfinfo*,char const*,char const*) ; 

__attribute__((used)) static int patch_one_symbol(struct vdso_elfinfo *e, const char *orig,
			    const char *new_target, bool elf64)
{
	if (elf64)
		return patchsym64(e, orig, new_target);
	else
		return patchsym32(e, orig, new_target);
}