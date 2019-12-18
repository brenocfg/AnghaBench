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
typedef  int /*<<< orphan*/  u32 ;
struct uasm_reloc {int dummy; } ;

/* Variables and functions */
 unsigned int _PAGE_ACCESSED ; 
 unsigned int _PAGE_VALID ; 
 int /*<<< orphan*/  iPTE_SW (int /*<<< orphan*/ **,struct uasm_reloc**,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void
build_make_valid(u32 **p, struct uasm_reloc **r, unsigned int pte,
		 unsigned int ptr, unsigned int scratch)
{
	unsigned int mode = _PAGE_VALID | _PAGE_ACCESSED;

	iPTE_SW(p, r, pte, ptr, mode, scratch);
}