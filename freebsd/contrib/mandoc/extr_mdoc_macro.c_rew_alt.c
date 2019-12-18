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
typedef  enum roff_tok { ____Placeholder_roff_tok } roff_tok ;

/* Variables and functions */
#define  MDOC_Ac 143 
 int MDOC_Ao ; 
#define  MDOC_Bc 142 
 int MDOC_Bd ; 
 int MDOC_Bf ; 
 int MDOC_Bk ; 
 int MDOC_Bl ; 
 int MDOC_Bo ; 
#define  MDOC_Brc 141 
 int MDOC_Bro ; 
#define  MDOC_Dc 140 
 int MDOC_Do ; 
#define  MDOC_Ec 139 
#define  MDOC_Ed 138 
#define  MDOC_Ef 137 
#define  MDOC_Ek 136 
#define  MDOC_El 135 
 int MDOC_Eo ; 
#define  MDOC_Fc 134 
 int MDOC_Fo ; 
#define  MDOC_Oc 133 
 int MDOC_Oo ; 
#define  MDOC_Pc 132 
 int MDOC_Po ; 
#define  MDOC_Qc 131 
 int MDOC_Qo ; 
#define  MDOC_Re 130 
 int MDOC_Rs ; 
#define  MDOC_Sc 129 
 int MDOC_So ; 
#define  MDOC_Xc 128 
 int MDOC_Xo ; 

__attribute__((used)) static enum roff_tok
rew_alt(enum roff_tok tok)
{
	switch (tok) {
	case MDOC_Ac:
		return MDOC_Ao;
	case MDOC_Bc:
		return MDOC_Bo;
	case MDOC_Brc:
		return MDOC_Bro;
	case MDOC_Dc:
		return MDOC_Do;
	case MDOC_Ec:
		return MDOC_Eo;
	case MDOC_Ed:
		return MDOC_Bd;
	case MDOC_Ef:
		return MDOC_Bf;
	case MDOC_Ek:
		return MDOC_Bk;
	case MDOC_El:
		return MDOC_Bl;
	case MDOC_Fc:
		return MDOC_Fo;
	case MDOC_Oc:
		return MDOC_Oo;
	case MDOC_Pc:
		return MDOC_Po;
	case MDOC_Qc:
		return MDOC_Qo;
	case MDOC_Re:
		return MDOC_Rs;
	case MDOC_Sc:
		return MDOC_So;
	case MDOC_Xc:
		return MDOC_Xo;
	default:
		return tok;
	}
}