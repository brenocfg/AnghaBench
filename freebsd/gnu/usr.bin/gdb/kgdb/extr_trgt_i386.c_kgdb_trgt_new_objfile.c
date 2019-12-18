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
struct objfile {int dummy; } ;

/* Variables and functions */
 int kgdb_parse (char*) ; 
 int ofs_fix ; 

void
kgdb_trgt_new_objfile(struct objfile *objfile)
{

	/*
	 * In revision 1.117 of i386/i386/exception.S trap handlers
	 * were changed to pass trapframes by reference rather than
	 * by value.  Detect this by seeing if the first instruction
	 * at the 'calltrap' label is a "push %esp" which has the
	 * opcode 0x54.
	 */
	if (kgdb_parse("((char *)calltrap)[0]") == 0x54)
		ofs_fix = 4;
	else
		ofs_fix = 0;
}