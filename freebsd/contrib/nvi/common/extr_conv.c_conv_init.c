#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ iconv_t ;
struct TYPE_9__ {scalar_t__* id; void* input2int; int /*<<< orphan*/  int2file; void* file2int; int /*<<< orphan*/  int2sys; void* sys2int; } ;
struct TYPE_8__ {TYPE_6__ conv; } ;
typedef  TYPE_1__ SCR ;

/* Variables and functions */
 int /*<<< orphan*/  BCOPY (TYPE_6__*,TYPE_6__*,int) ; 
 int IC_IE_TO_UTF16 ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  OS_STRDUP ; 
 int /*<<< orphan*/  O_INPUTENCODING ; 
 int /*<<< orphan*/  codeset () ; 
 int /*<<< orphan*/  conv_enc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cs_char2int ; 
 int /*<<< orphan*/  cs_int2char ; 
 void* fe_char2int ; 
 int /*<<< orphan*/  fe_int2char ; 
 void* ie_char2int ; 
 int /*<<< orphan*/  int2raw ; 
 int /*<<< orphan*/  o_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* raw2int ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void
conv_init(SCR *orig, SCR *sp)
{
	int i;

	if (orig == NULL)
		setlocale(LC_ALL, "");
	if (orig != NULL)
		BCOPY(&orig->conv, &sp->conv, 1);
#ifdef USE_WIDECHAR
	else {
		char *ctype = setlocale(LC_CTYPE, NULL);

		/*
		 * XXX
		 * This hack fixes the libncursesw issue on FreeBSD.
		 */
		if (!strcmp(ctype, "ko_KR.CP949"))
			setlocale(LC_CTYPE, "ko_KR.eucKR");
		else if (!strcmp(ctype, "zh_CN.GB2312"))
			setlocale(LC_CTYPE, "zh_CN.eucCN");
		else if (!strcmp(ctype, "zh_CN.GBK"))
			setlocale(LC_CTYPE, "zh_CN.GB18030");

		/*
		 * Switch to 8bit mode if locale is C;
		 * LC_CTYPE should be reseted to C if unmatched.
		 */
		if (!strcmp(ctype, "C") || !strcmp(ctype, "POSIX")) {
			sp->conv.sys2int = sp->conv.file2int = raw2int;
			sp->conv.int2sys = sp->conv.int2file = int2raw;
			sp->conv.input2int = raw2int;
		} else {
			sp->conv.sys2int = cs_char2int;
			sp->conv.int2sys = cs_int2char;
			sp->conv.file2int = fe_char2int;
			sp->conv.int2file = fe_int2char;
			sp->conv.input2int = ie_char2int;
		}
#ifdef USE_ICONV
		o_set(sp, O_INPUTENCODING, OS_STRDUP, codeset(), 0);
#endif
	}
#endif

	/* iconv descriptors must be distinct to screens. */
	for (i = 0; i <= IC_IE_TO_UTF16; ++i)
		sp->conv.id[i] = (iconv_t)-1;
#ifdef USE_ICONV
	conv_enc(sp, O_INPUTENCODING, 0);
#endif
}