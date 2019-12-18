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
struct nlist {int n_type; int /*<<< orphan*/  n_value; } ;

/* Variables and functions */
#define  AUX_FUNC 169 
#define  AUX_OBJECT 168 
 scalar_t__ BIND_WEAK ; 
#define  N_ABS 167 
 int N_AUX (struct nlist const*) ; 
#define  N_BCOMM 166 
#define  N_BINCL 165 
 scalar_t__ N_BIND (struct nlist const*) ; 
#define  N_BSLINE 164 
#define  N_BSS 163 
#define  N_COMM 162 
#define  N_DATA 161 
#define  N_DSLINE 160 
#define  N_ECOML 159 
#define  N_ECOMM 158 
#define  N_EINCL 157 
#define  N_ENTRY 156 
#define  N_EXCL 155 
 int N_EXT ; 
#define  N_FN 154 
#define  N_FNAME 153 
#define  N_FUN 152 
#define  N_GSYM 151 
#define  N_INDR 150 
#define  N_LBRAC 149 
#define  N_LCSYM 148 
#define  N_LENG 147 
#define  N_LSYM 146 
#define  N_MAIN 145 
#define  N_PC 144 
#define  N_PSYM 143 
#define  N_RBRAC 142 
#define  N_RSYM 141 
#define  N_SETA 140 
#define  N_SETB 139 
#define  N_SETD 138 
#define  N_SETT 137 
#define  N_SETV 136 
#define  N_SIZE 135 
#define  N_SLINE 134 
#define  N_SO 133 
#define  N_SOL 132 
#define  N_SSYM 131 
#define  N_STSYM 130 
#define  N_TEXT 129 
#define  N_UNDF 128 
 int /*<<< orphan*/  printf (char*,char,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char toupper (char) ; 

__attribute__((used)) static void
dump_sym(const struct nlist *np)
{
    char type[8];
    char aux[8];
    char weak;
    char *p;

    switch (np->n_type & ~N_EXT) {
    case N_UNDF:	strcpy(type, "undf");  break;
    case N_ABS:		strcpy(type, "abs");  break;
    case N_TEXT:	strcpy(type, "text");  break;
    case N_DATA:	strcpy(type, "data");  break;
    case N_BSS:		strcpy(type, "bss");  break;
    case N_INDR:	strcpy(type, "indr");  break;
    case N_SIZE:	strcpy(type, "size");  break;
    case N_COMM:	strcpy(type, "comm");  break;
    case N_SETA:	strcpy(type, "seta");  break;
    case N_SETT:	strcpy(type, "sett");  break;
    case N_SETD:	strcpy(type, "setd");  break;
    case N_SETB:	strcpy(type, "setb");  break;
    case N_SETV:	strcpy(type, "setv");  break;
    case N_FN:		strcpy(type, np->n_type&N_EXT ? "fn" : "warn");  break;
    case N_GSYM:	strcpy(type, "gsym");  break;
    case N_FNAME:	strcpy(type, "fname");  break;
    case N_FUN:		strcpy(type, "fun");  break;
    case N_STSYM:	strcpy(type, "stsym");  break;
    case N_LCSYM:	strcpy(type, "lcsym");  break;
    case N_MAIN:	strcpy(type, "main");  break;
    case N_PC:		strcpy(type, "pc");  break;
    case N_RSYM:	strcpy(type, "rsym");  break;
    case N_SLINE:	strcpy(type, "sline");  break;
    case N_DSLINE:	strcpy(type, "dsline");  break;
    case N_BSLINE:	strcpy(type, "bsline");  break;
    case N_SSYM:	strcpy(type, "ssym");  break;
    case N_SO:		strcpy(type, "so");  break;
    case N_LSYM:	strcpy(type, "lsym");  break;
    case N_BINCL:	strcpy(type, "bincl");  break;
    case N_SOL:		strcpy(type, "sol");  break;
    case N_PSYM:	strcpy(type, "psym");  break;
    case N_EINCL:	strcpy(type, "eincl");  break;
    case N_ENTRY:	strcpy(type, "entry");  break;
    case N_LBRAC:	strcpy(type, "lbrac");  break;
    case N_EXCL:	strcpy(type, "excl");  break;
    case N_RBRAC:	strcpy(type, "rbrac");  break;
    case N_BCOMM:	strcpy(type, "bcomm");  break;
    case N_ECOMM:	strcpy(type, "ecomm");  break;
    case N_ECOML:	strcpy(type, "ecoml");  break;
    case N_LENG:	strcpy(type, "leng");  break;
    default:
	snprintf(type, sizeof type, "%#02x", np->n_type);
	break;
    }

    if (np->n_type & N_EXT && type[0] != '0')
	for (p = type;  *p != '\0';  ++p)
	    *p = toupper(*p);

    switch (N_AUX(np)) {
    case 0:		strcpy(aux, "");  break;
    case AUX_OBJECT:	strcpy(aux, "objt");  break;
    case AUX_FUNC:	strcpy(aux, "func");  break;
    default:		snprintf(aux, sizeof aux, "%#01x", N_AUX(np));  break;
    }

    weak = N_BIND(np) == BIND_WEAK ? 'w' : ' ';

    printf("%c%-6s %-4s %8lx", weak, type, aux, np->n_value);
}