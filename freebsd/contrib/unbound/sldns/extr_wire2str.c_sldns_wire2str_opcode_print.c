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
struct TYPE_3__ {unsigned int name; } ;
typedef  TYPE_1__ sldns_lookup_table ;

/* Variables and functions */
 TYPE_1__* sldns_lookup_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_opcodes ; 
 int sldns_str_print (char**,size_t*,char*,unsigned int) ; 

int sldns_wire2str_opcode_print(char** s, size_t* slen, int opcode)
{
	sldns_lookup_table *lt = sldns_lookup_by_id(sldns_opcodes, opcode);
	if (lt && lt->name) {
		return sldns_str_print(s, slen, "%s", lt->name);
	}
	return sldns_str_print(s, slen, "OPCODE%u", (unsigned)opcode);
}