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
struct TYPE_3__ {int /*<<< orphan*/  r_info; } ;
typedef  TYPE_1__ Elf_Rela ;

/* Variables and functions */
 int ELF32_R_TYPE (int /*<<< orphan*/ ) ; 
#define  R_PARISC_PCREL17F 129 
#define  R_PARISC_PCREL22F 128 

__attribute__((used)) static inline unsigned long count_stubs(const Elf_Rela *rela, unsigned long n)
{
	unsigned long cnt = 0;

	for (; n > 0; n--, rela++)
	{
		switch (ELF32_R_TYPE(rela->r_info)) {
			case R_PARISC_PCREL17F:
			case R_PARISC_PCREL22F:
				cnt++;
		}
	}

	return cnt;
}