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
typedef  scalar_t__ db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_read_bytes (int /*<<< orphan*/ ,size_t,char*) ; 
 int /*<<< orphan*/  md_printins (int,scalar_t__) ; 
 scalar_t__ vtophys (int /*<<< orphan*/ ) ; 

db_addr_t
db_disasm(db_addr_t loc, bool altfmt)

{
	int ins;

	if (vtophys((vm_offset_t)loc)) {
		db_read_bytes((vm_offset_t)loc, (size_t)sizeof(int),
		    (char *)&ins);
		md_printins(ins, loc);
	}

	return (loc + sizeof(int));
}