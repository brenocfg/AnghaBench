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
struct TYPE_3__ {long sh_size; scalar_t__ sh_addralign; } ;
typedef  TYPE_1__ Elf_Shdr ;

/* Variables and functions */
 long ALIGN (unsigned long,int) ; 

__attribute__((used)) static long get_offset(unsigned long *size, Elf_Shdr *sechdr)
{
	long ret;

	ret = ALIGN(*size, sechdr->sh_addralign ? : 1);
	*size = ret + sechdr->sh_size;
	return ret;
}