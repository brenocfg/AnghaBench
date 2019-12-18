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
typedef  int /*<<< orphan*/  OpCodes ;

/* Variables and functions */
 char* fmt_intarg (int /*<<< orphan*/ ,int) ; 
 char* lookup_opcode_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void
dump_cfg_fmtint(OpCodes code, int val)
{
	printf("%s %s\n", lookup_opcode_name(code), fmt_intarg(code, val));
}