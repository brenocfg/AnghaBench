#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Tree ;
struct TYPE_4__ {char* type; } ;

/* Variables and functions */
#define  ADD 151 
#define  AND 150 
#define  ASGN 149 
#define  BAND 148 
#define  BCOM 147 
#define  BOR 146 
#define  BXOR 145 
#define  COND 144 
#define  DIV 143 
#define  EQ 142 
#define  GE 141 
#define  GT 140 
#define  INDIR 139 
#define  LE 138 
#define  LSH 137 
#define  LT 136 
#define  MOD 135 
#define  MUL 134 
#define  NE 133 
#define  NEG 132 
#define  NOT 131 
#define  OR 130 
#define  RSH 129 
#define  SUB 128 
 int /*<<< orphan*/  assert (char*) ; 
 int /*<<< orphan*/  error (char*,char*,char*,...) ; 
 int generic (int) ; 

void typeerror(int op, Tree l, Tree r) {
	int i;
	static struct { int op; char *name; } ops[] = {
		{ASGN, "="},	{INDIR, "*"},	{NEG,  "-"},
		{ADD,  "+"},	{SUB,   "-"},	{LSH,  "<<"},
		{MOD,  "%"},	{RSH,   ">>"},	{BAND, "&"},
		{BCOM, "~"},	{BOR,   "|"},	{BXOR, "^"},
		{DIV,  "/"},	{MUL,   "*"},	{EQ,   "=="},
		{GE,   ">="},	{GT,    ">"},	{LE,   "<="},
		{LT,   "<"},	{NE,    "!="},	{AND,  "&&"},
		{NOT,  "!"},	{OR,    "||"},	{COND, "?:"},
		{0, 0}
	};

	op = generic(op);
	for (i = 0; ops[i].op; i++)
		if (op == ops[i].op)
			break;
	assert(ops[i].name);
	if (r)
		error("operands of %s have illegal types `%t' and `%t'\n",
			ops[i].name, l->type, r->type);
	else
		error("operand of unary %s has illegal type `%t'\n", ops[i].name,
			l->type);
}