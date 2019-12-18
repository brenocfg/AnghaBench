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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_disasm_interface ; 
 int /*<<< orphan*/  disasm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

vm_offset_t
db_disasm(vm_offset_t loc, bool altfmt)
{

	return (disasm(&db_disasm_interface, loc, altfmt));
}