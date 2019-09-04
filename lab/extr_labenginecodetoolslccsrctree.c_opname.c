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

/* Variables and functions */
 scalar_t__ AND ; 
 scalar_t__ FIELD ; 
 size_t NELEMS (char**) ; 
 scalar_t__ generic (int) ; 
 size_t opindex (int) ; 
 size_t opsize (int) ; 
 size_t optype (int) ; 
 char* stringd (size_t) ; 
 char* stringf (char*,char*,char*,char*) ; 

char *opname(int op) {
	static char *opnames[] = {
	"",
	"CNST",
	"ARG",
	"ASGN",
	"INDIR",
	"CVC",
	"CVD",
	"CVF",
	"CVI",
	"CVP",
	"CVS",
	"CVU",
	"NEG",
	"CALL",
	"*LOAD*",
	"RET",
	"ADDRG",
	"ADDRF",
	"ADDRL",
	"ADD",
	"SUB",
	"LSH",
	"MOD",
	"RSH",
	"BAND",
	"BCOM",
	"BOR",
	"BXOR",
	"DIV",
	"MUL",
	"EQ",
	"GE",
	"GT",
	"LE",
	"LT",
	"NE",
	"JUMP",
	"LABEL",
	"AND",
	"NOT",
	"OR",
	"COND",
	"RIGHT",
	"FIELD"
	}, *suffixes[] = {
		"0", "F", "D", "C", "S", "I", "U", "P", "V", "B",
		"10","11","12","13","14","15"
	};

	if (generic(op) >= AND && generic(op) <= FIELD && opsize(op) == 0)
		return opnames[opindex(op)];
	return stringf("%s%s%s",
		opindex(op) > 0 && opindex(op) < NELEMS(opnames) ?
			opnames[opindex(op)] : stringd(opindex(op)),
		suffixes[optype(op)], opsize(op) > 0 ? stringd(opsize(op)) : "");
}