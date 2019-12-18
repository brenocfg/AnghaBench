#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int recno_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/ * ep; } ;
typedef  TYPE_1__ SCR ;
typedef  int /*<<< orphan*/  EXF ;

/* Variables and functions */
 int /*<<< orphan*/  OS_STRDUP ; 
 int /*<<< orphan*/  O_FILEENCODING ; 
 int /*<<< orphan*/  O_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_STR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* codeset () ; 
 int /*<<< orphan*/  conv_enc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_rget (TYPE_1__*,int /*<<< orphan*/ ,char**,size_t*) ; 
 int looks_utf8 (char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  o_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
file_encinit(SCR *sp)
{
#if defined(USE_WIDECHAR) && defined(USE_ICONV)
	size_t len;
	char *p;
	size_t blen = 0;
	char buf[4096];	/* not need to be '\0'-terminated */
	recno_t ln = 1;
	EXF *ep;

	ep = sp->ep;

	while (!db_rget(sp, ln++, &p, &len)) {
		if (blen + len > sizeof(buf))
			len = sizeof(buf) - blen;
		memcpy(buf + blen, p, len);
		blen += len;
		if (blen == sizeof(buf))
			break;
		else
			buf[blen++] = '\n';
	}

	/*
	 * Detect UTF-8 and fallback to the locale/preset encoding.
	 *
	 * XXX
	 * A manually set O_FILEENCODING indicates the "fallback
	 * encoding", but UTF-8, which can be safely detected, is not
	 * inherited from the old screen.
	 */
	if (looks_utf8(buf, blen) > 1)
		o_set(sp, O_FILEENCODING, OS_STRDUP, "utf-8", 0);
	else if (!O_ISSET(sp, O_FILEENCODING) ||
	    !strcasecmp(O_STR(sp, O_FILEENCODING), "utf-8"))
		o_set(sp, O_FILEENCODING, OS_STRDUP, codeset(), 0);

	conv_enc(sp, O_FILEENCODING, 0);
#endif
}