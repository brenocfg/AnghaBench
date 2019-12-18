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
struct TYPE_3__ {int ctype; } ;
typedef  TYPE_1__ ctype_node_t ;

/* Variables and functions */
#define  T_ISALNUM 144 
#define  T_ISALPHA 143 
#define  T_ISBLANK 142 
#define  T_ISCNTRL 141 
#define  T_ISDIGIT 140 
#define  T_ISENGLISH 139 
#define  T_ISGRAPH 138 
#define  T_ISIDEOGRAM 137 
#define  T_ISLOWER 136 
#define  T_ISNUMBER 135 
#define  T_ISPHONOGRAM 134 
#define  T_ISPRINT 133 
#define  T_ISPUNCT 132 
#define  T_ISSPACE 131 
#define  T_ISSPECIAL 130 
#define  T_ISUPPER 129 
#define  T_ISXDIGIT 128 
 int _E1 ; 
 int _E2 ; 
 int _E3 ; 
 int _E4 ; 
 int _E5 ; 
 int _ISALPHA ; 
 int _ISBLANK ; 
 int _ISCNTRL ; 
 int _ISDIGIT ; 
 int _ISGRAPH ; 
 int _ISLOWER ; 
 int _ISPRINT ; 
 int _ISPUNCT ; 
 int _ISSPACE ; 
 int _ISUPPER ; 
 int _ISXDIGIT ; 
 int /*<<< orphan*/  errf (char*) ; 
 int last_kw ; 

__attribute__((used)) static void
add_ctype_impl(ctype_node_t *ctn)
{
	switch (last_kw) {
	case T_ISUPPER:
		ctn->ctype |= (_ISUPPER | _ISALPHA | _ISGRAPH | _ISPRINT);
		break;
	case T_ISLOWER:
		ctn->ctype |= (_ISLOWER | _ISALPHA | _ISGRAPH | _ISPRINT);
		break;
	case T_ISALPHA:
		ctn->ctype |= (_ISALPHA | _ISGRAPH | _ISPRINT);
		break;
	case T_ISDIGIT:
		ctn->ctype |= (_ISDIGIT | _ISGRAPH | _ISPRINT | _ISXDIGIT | _E4);
		break;
	case T_ISSPACE:
		/*
		 * This can be troublesome as <form-feed>, <newline>,
		 * <carriage-return>, <tab>, and <vertical-tab> are defined both
		 * as space and cntrl, and POSIX doesn't allow cntrl/print
		 * combination.  We will take care of this in dump_ctype().
		 */
		ctn->ctype |= (_ISSPACE | _ISPRINT);
		break;
	case T_ISCNTRL:
		ctn->ctype |= _ISCNTRL;
		break;
	case T_ISGRAPH:
		ctn->ctype |= (_ISGRAPH | _ISPRINT);
		break;
	case T_ISPRINT:
		ctn->ctype |= _ISPRINT;
		break;
	case T_ISPUNCT:
		ctn->ctype |= (_ISPUNCT | _ISGRAPH | _ISPRINT);
		break;
	case T_ISXDIGIT:
		ctn->ctype |= (_ISXDIGIT | _ISPRINT);
		break;
	case T_ISBLANK:
		ctn->ctype |= (_ISBLANK | _ISSPACE);
		break;
	case T_ISPHONOGRAM:
		ctn->ctype |= (_E1 | _ISPRINT | _ISGRAPH);
		break;
	case T_ISIDEOGRAM:
		ctn->ctype |= (_E2 | _ISPRINT | _ISGRAPH);
		break;
	case T_ISENGLISH:
		ctn->ctype |= (_E3 | _ISPRINT | _ISGRAPH);
		break;
	case T_ISNUMBER:
		ctn->ctype |= (_E4 | _ISPRINT | _ISGRAPH);
		break;
	case T_ISSPECIAL:
		ctn->ctype |= (_E5 | _ISPRINT | _ISGRAPH);
		break;
	case T_ISALNUM:
		/*
		 * We can't do anything with this.  The character
		 * should already be specified as a digit or alpha.
		 */
		break;
	default:
		errf("not a valid character class");
	}
}