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
struct KeyFuncs {unsigned char* name; int /*<<< orphan*/  func; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ XmapVal ;
typedef  unsigned char Char ;

/* Variables and functions */
 unsigned char* CGETS (int,int,char*) ; 
 struct KeyFuncs* FuncNames ; 
 int /*<<< orphan*/  STRBB ; 
 int /*<<< orphan*/  STRQQ ; 
#define  XK_CMD 130 
#define  XK_EXE 129 
#define  XK_STR 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  cleanup_push (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (unsigned char*) ; 
 unsigned char* unparsestring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 
 int /*<<< orphan*/  xprintf (char const*,unsigned char const*) ; 

void
printOne(const Char *key, const XmapVal *val, int ntype)
{
    struct KeyFuncs *fp;
    static const char *fmt = "%s\n";

    xprintf("%-15S-> ", key);
    if (val != NULL)
	switch (ntype) {
	case XK_STR:
	case XK_EXE: {
	    unsigned char *p;

	    p = unparsestring(&val->str, ntype == XK_STR ? STRQQ : STRBB);
	    cleanup_push(p, xfree);
	    xprintf(fmt, p);
	    cleanup_until(p);
	    break;
	}
	case XK_CMD:
	    for (fp = FuncNames; fp->name; fp++)
		if (val->cmd == fp->func)
		    xprintf(fmt, fp->name);
		break;
	default:
	    abort();
	    break;
	}
    else
	xprintf(fmt, CGETS(9, 7, "no input"));
}