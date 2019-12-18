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
struct vdso_image {int /*<<< orphan*/  data; } ;
struct vdso_elfinfo64 {void* dynstr; void* dynsym; int /*<<< orphan*/  dynsymsize; int /*<<< orphan*/  hdr; } ;
struct TYPE_2__ {struct vdso_elfinfo64 elf64; } ;
struct vdso_elfinfo {TYPE_1__ u; } ;

/* Variables and functions */
 int ENODEV ; 
 void* one_section64 (struct vdso_elfinfo64*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int find_sections64(const struct vdso_image *image, struct vdso_elfinfo *_e)
{
	struct vdso_elfinfo64 *e = &_e->u.elf64;

	e->hdr = image->data;
	e->dynsym = one_section64(e, ".dynsym", &e->dynsymsize);
	e->dynstr = one_section64(e, ".dynstr", NULL);

	if (!e->dynsym || !e->dynstr) {
		pr_err("VDSO64: Missing symbol sections.\n");
		return -ENODEV;
	}
	return 0;
}