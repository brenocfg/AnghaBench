#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* elf_file_t ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ address; int /*<<< orphan*/  ef_name; scalar_t__ ef_verbose; } ;
typedef  scalar_t__ Elf_Off ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  bcopy (scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,long,long) ; 

__attribute__((used)) static int
ef_obj_seg_read(elf_file_t ef, Elf_Off offset, size_t len, void *dest)
{

	if (offset + len > ef->size) {
		if (ef->ef_verbose)
			warnx("ef_obj_seg_read(%s): bad offset/len (%lx:%ld)",
			    ef->ef_name, (long)offset, (long)len);
		return (EFAULT);
	}
	bcopy(ef->address + offset, dest, len);
	return (0);
}