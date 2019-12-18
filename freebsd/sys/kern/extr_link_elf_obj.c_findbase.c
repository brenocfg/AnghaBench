#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* elf_file_t ;
struct TYPE_5__ {int nprogtab; TYPE_1__* progtab; } ;
struct TYPE_4__ {int sec; scalar_t__ addr; } ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */

__attribute__((used)) static Elf_Addr
findbase(elf_file_t ef, int sec)
{
	int i;
	Elf_Addr base = 0;

	for (i = 0; i < ef->nprogtab; i++) {
		if (sec == ef->progtab[i].sec) {
			base = (Elf_Addr)ef->progtab[i].addr;
			break;
		}
	}
	return base;
}