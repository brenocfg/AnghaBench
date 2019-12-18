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
typedef  int /*<<< orphan*/  Elf_Auxinfo ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/ * __elf_aux_vector ; 
 scalar_t__ environ ; 

__attribute__((used)) static void
init_aux_vector_once(void)
{
	Elf_Addr *sp;

	sp = (Elf_Addr *)environ;
	while (*sp++ != 0)
		;
	__elf_aux_vector = (Elf_Auxinfo *)sp;
}