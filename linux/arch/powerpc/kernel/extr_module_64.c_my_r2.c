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
struct TYPE_4__ {size_t toc_section; } ;
struct module {TYPE_1__ arch; } ;
struct TYPE_5__ {int sh_addr; } ;
typedef  TYPE_2__ Elf64_Shdr ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long my_r2(const Elf64_Shdr *sechdrs, struct module *me)
{
	return (sechdrs[me->arch.toc_section].sh_addr & ~0xfful) + 0x8000;
}