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
typedef  enum e_modifier { ____Placeholder_e_modifier } e_modifier ;
typedef  int /*<<< orphan*/  EFT ;

/* Variables and functions */
 int /*<<< orphan*/  FMTCHECK_CHARPOINTER ; 
 int /*<<< orphan*/  FMTCHECK_DOUBLE ; 
 int /*<<< orphan*/  FMTCHECK_INT ; 
 int /*<<< orphan*/  FMTCHECK_INTMAXT ; 
 int /*<<< orphan*/  FMTCHECK_INTMAXTPOINTER ; 
 int /*<<< orphan*/  FMTCHECK_INTPOINTER ; 
 int /*<<< orphan*/  FMTCHECK_LONG ; 
 int /*<<< orphan*/  FMTCHECK_LONGDOUBLE ; 
 int /*<<< orphan*/  FMTCHECK_LONGPOINTER ; 
 int /*<<< orphan*/  FMTCHECK_PTRDIFFT ; 
 int /*<<< orphan*/  FMTCHECK_PTRDIFFTPOINTER ; 
 int /*<<< orphan*/  FMTCHECK_QUAD ; 
 int /*<<< orphan*/  FMTCHECK_QUADPOINTER ; 
 int /*<<< orphan*/  FMTCHECK_SHORTPOINTER ; 
 int /*<<< orphan*/  FMTCHECK_SIZET ; 
 int /*<<< orphan*/  FMTCHECK_SIZETPOINTER ; 
 int /*<<< orphan*/  FMTCHECK_STRING ; 
 int /*<<< orphan*/  FMTCHECK_UNKNOWN ; 
 int /*<<< orphan*/  FMTCHECK_WINTT ; 
 int /*<<< orphan*/  FMTCHECK_WSTRING ; 
#define  MOD_CHAR 136 
#define  MOD_INTMAXT 135 
#define  MOD_LONG 134 
#define  MOD_LONGDOUBLE 133 
#define  MOD_NONE 132 
#define  MOD_PTRDIFFT 131 
#define  MOD_QUAD 130 
#define  MOD_SHORT 129 
#define  MOD_SIZET 128 
 int /*<<< orphan*/  RETURN (char const**,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char const) ; 

__attribute__((used)) static EFT
get_next_format_from_precision(const char **pf)
{
	enum e_modifier	modifier;
	const char	*f;

	f = *pf;
	switch (*f) {
	case 'h':
		f++;
		if (!*f) RETURN(pf,f,FMTCHECK_UNKNOWN);
		if (*f == 'h') {
			f++;
			modifier = MOD_CHAR;
		} else {
			modifier = MOD_SHORT;
		}
		break;
	case 'j':
		f++;
		modifier = MOD_INTMAXT;
		break;
	case 'l':
		f++;
		if (!*f) RETURN(pf,f,FMTCHECK_UNKNOWN);
		if (*f == 'l') {
			f++;
			modifier = MOD_QUAD;
		} else {
			modifier = MOD_LONG;
		}
		break;
	case 'q':
		f++;
		modifier = MOD_QUAD;
		break;
	case 't':
		f++;
		modifier = MOD_PTRDIFFT;
		break;
	case 'z':
		f++;
		modifier = MOD_SIZET;
		break;
	case 'L':
		f++;
		modifier = MOD_LONGDOUBLE;
		break;
	default:
		modifier = MOD_NONE;
		break;
	}
	if (!*f) RETURN(pf,f,FMTCHECK_UNKNOWN);
	if (strchr("diouxX", *f)) {
		switch (modifier) {
		case MOD_LONG:
			RETURN(pf,f,FMTCHECK_LONG);
		case MOD_QUAD:
			RETURN(pf,f,FMTCHECK_QUAD);
		case MOD_INTMAXT:
			RETURN(pf,f,FMTCHECK_INTMAXT);
		case MOD_PTRDIFFT:
			RETURN(pf,f,FMTCHECK_PTRDIFFT);
		case MOD_SIZET:
			RETURN(pf,f,FMTCHECK_SIZET);
		case MOD_CHAR:
		case MOD_SHORT:
		case MOD_NONE:
			RETURN(pf,f,FMTCHECK_INT);
		default:
			RETURN(pf,f,FMTCHECK_UNKNOWN);
		}
	}
	if (*f == 'n') {
		switch (modifier) {
		case MOD_CHAR:
			RETURN(pf,f,FMTCHECK_CHARPOINTER);
		case MOD_SHORT:
			RETURN(pf,f,FMTCHECK_SHORTPOINTER);
		case MOD_LONG:
			RETURN(pf,f,FMTCHECK_LONGPOINTER);
		case MOD_QUAD:
			RETURN(pf,f,FMTCHECK_QUADPOINTER);
		case MOD_INTMAXT:
			RETURN(pf,f,FMTCHECK_INTMAXTPOINTER);
		case MOD_PTRDIFFT:
			RETURN(pf,f,FMTCHECK_PTRDIFFTPOINTER);
		case MOD_SIZET:
			RETURN(pf,f,FMTCHECK_SIZETPOINTER);
		case MOD_NONE:
			RETURN(pf,f,FMTCHECK_INTPOINTER);
		default:
			RETURN(pf,f,FMTCHECK_UNKNOWN);
		}
	}
	if (strchr("DOU", *f)) {
		if (modifier != MOD_NONE)
			RETURN(pf,f,FMTCHECK_UNKNOWN);
		RETURN(pf,f,FMTCHECK_LONG);
	}
#ifndef NO_FLOATING_POINT
	if (strchr("aAeEfFgG", *f)) {
		switch (modifier) {
		case MOD_LONGDOUBLE:
			RETURN(pf,f,FMTCHECK_LONGDOUBLE);
		case MOD_LONG:
		case MOD_NONE:
			RETURN(pf,f,FMTCHECK_DOUBLE);
		default:
			RETURN(pf,f,FMTCHECK_UNKNOWN);
		}
	}
#endif
	if (*f == 'c') {
		switch (modifier) {
		case MOD_LONG:
			RETURN(pf,f,FMTCHECK_WINTT);
		case MOD_NONE:
			RETURN(pf,f,FMTCHECK_INT);
		default:
			RETURN(pf,f,FMTCHECK_UNKNOWN);
		}
	}
	if (*f == 'C') {
		if (modifier != MOD_NONE)
			RETURN(pf,f,FMTCHECK_UNKNOWN);
		RETURN(pf,f,FMTCHECK_WINTT);
	}
	if (*f == 's') {
		switch (modifier) {
		case MOD_LONG:
			RETURN(pf,f,FMTCHECK_WSTRING);
		case MOD_NONE:
			RETURN(pf,f,FMTCHECK_STRING);
		default:
			RETURN(pf,f,FMTCHECK_UNKNOWN);
		}
	}
	if (*f == 'S') {
		if (modifier != MOD_NONE)
			RETURN(pf,f,FMTCHECK_UNKNOWN);
		RETURN(pf,f,FMTCHECK_WSTRING);
	}
	if (*f == 'p') {
		if (modifier != MOD_NONE)
			RETURN(pf,f,FMTCHECK_UNKNOWN);
		RETURN(pf,f,FMTCHECK_LONG);
	}
	RETURN(pf,f,FMTCHECK_UNKNOWN);
	/*NOTREACHED*/
}