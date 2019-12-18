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
struct vdso_image {int dummy; } ;
struct vdso_elfinfo {int dummy; } ;

/* Variables and functions */
 int find_sections32 (struct vdso_image const*,struct vdso_elfinfo*) ; 
 int find_sections64 (struct vdso_image const*,struct vdso_elfinfo*) ; 

__attribute__((used)) static int find_sections(const struct vdso_image *image, struct vdso_elfinfo *e,
			 bool elf64)
{
	if (elf64)
		return find_sections64(image, e);
	else
		return find_sections32(image, e);
}