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
#define  MDOC_Ad 168 
#define  MDOC_An 167 
#define  MDOC_Ao 166 
#define  MDOC_Aq 165 
#define  MDOC_Ar 164 
#define  MDOC_Bo 163 
#define  MDOC_Bq 162 
#define  MDOC_Cd 161 
#define  MDOC_Cm 160 
#define  MDOC_Do 159 
#define  MDOC_Dq 158 
#define  MDOC_Dv 157 
#define  MDOC_Em 156 
#define  MDOC_Eo 155 
#define  MDOC_Er 154 
#define  MDOC_Ev 153 
#define  MDOC_Fa 152 
#define  MDOC_Fl 151 
#define  MDOC_Fn 150 
#define  MDOC_Fo 149 
#define  MDOC_Ic 148 
#define  MDOC_Li 147 
#define  MDOC_Ms 146 
#define  MDOC_Nm 145 
#define  MDOC_No 144 
#define  MDOC_Oo 143 
#define  MDOC_Op 142 
#define  MDOC_Pa 141 
#define  MDOC_Pf 140 
#define  MDOC_Po 139 
#define  MDOC_Pq 138 
#define  MDOC_Ql 137 
#define  MDOC_Qo 136 
#define  MDOC_So 135 
#define  MDOC_Sq 134 
#define  MDOC_Sx 133 
#define  MDOC_Sy 132 
#define  MDOC_Tn 131 
#define  MDOC_Va 130 
#define  MDOC_Vt 129 
#define  MDOC_Xr 128 

__attribute__((used)) static size_t
macro2len(enum roff_tok macro)
{

	switch (macro) {
	case MDOC_Ad:
		return 12;
	case MDOC_Ao:
		return 12;
	case MDOC_An:
		return 12;
	case MDOC_Aq:
		return 12;
	case MDOC_Ar:
		return 12;
	case MDOC_Bo:
		return 12;
	case MDOC_Bq:
		return 12;
	case MDOC_Cd:
		return 12;
	case MDOC_Cm:
		return 10;
	case MDOC_Do:
		return 10;
	case MDOC_Dq:
		return 12;
	case MDOC_Dv:
		return 12;
	case MDOC_Eo:
		return 12;
	case MDOC_Em:
		return 10;
	case MDOC_Er:
		return 17;
	case MDOC_Ev:
		return 15;
	case MDOC_Fa:
		return 12;
	case MDOC_Fl:
		return 10;
	case MDOC_Fo:
		return 16;
	case MDOC_Fn:
		return 16;
	case MDOC_Ic:
		return 10;
	case MDOC_Li:
		return 16;
	case MDOC_Ms:
		return 6;
	case MDOC_Nm:
		return 10;
	case MDOC_No:
		return 12;
	case MDOC_Oo:
		return 10;
	case MDOC_Op:
		return 14;
	case MDOC_Pa:
		return 32;
	case MDOC_Pf:
		return 12;
	case MDOC_Po:
		return 12;
	case MDOC_Pq:
		return 12;
	case MDOC_Ql:
		return 16;
	case MDOC_Qo:
		return 12;
	case MDOC_So:
		return 12;
	case MDOC_Sq:
		return 12;
	case MDOC_Sy:
		return 6;
	case MDOC_Sx:
		return 16;
	case MDOC_Tn:
		return 10;
	case MDOC_Va:
		return 12;
	case MDOC_Vt:
		return 12;
	case MDOC_Xr:
		return 10;
	default:
		break;
	};
	return 0;
}