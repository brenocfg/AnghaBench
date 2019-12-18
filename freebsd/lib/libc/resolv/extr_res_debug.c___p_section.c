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
struct res_sym {int dummy; } ;

/* Variables and functions */
 struct res_sym* __p_default_section_syms ; 
 struct res_sym* __p_update_section_syms ; 
#define  ns_o_update 128 
 char const* sym_ntos (struct res_sym const*,int,int*) ; 

const char *
p_section(int section, int opcode) {
	const struct res_sym *symbols;

	switch (opcode) {
	case ns_o_update:
		symbols = __p_update_section_syms;
		break;
	default:
		symbols = __p_default_section_syms;
		break;
	}
	return (sym_ntos(symbols, section, (int *)0));
}