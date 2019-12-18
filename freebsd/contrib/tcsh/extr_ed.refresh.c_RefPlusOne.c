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
typedef  int Char ;

/* Variables and functions */
 int CHAR ; 
 int CTL_ESC (char) ; 
 int /*<<< orphan*/  Cursor ; 
 scalar_t__ CursorH ; 
 int* InputBuf ; 
 int /*<<< orphan*/  LastChar ; 
 int MakeLiteral (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MarkIsSet ; 
#define  NLSCLASS_CTRL 129 
#define  NLSCLASS_ILLEGAL 128 
 int NLSClassify (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutPlusOne (int,int) ; 
 int /*<<< orphan*/  Refresh () ; 
 int /*<<< orphan*/  STRhighlight ; 
 int /*<<< orphan*/  StartHighlight () ; 
 int /*<<< orphan*/  StopHighlight () ; 
 scalar_t__ TermH ; 
 int* _toascii ; 
 int* _toebcdic ; 
 int /*<<< orphan*/  adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush () ; 
 scalar_t__ rprompt_h ; 

void
RefPlusOne(int l)
{				/* we added just one char, handle it fast.
				 * assumes that screen cursor == real cursor */
    Char *cp, c;
    int w;

    if (Cursor != LastChar) {
	Refresh();		/* too hard to handle */
	return;
    }
    if (rprompt_h != 0 && (TermH - CursorH - rprompt_h < 3)) {
	Refresh();		/* clear out rprompt if less than one char gap*/
	return;
    }
    cp = Cursor - l;
    c = *cp & CHAR;
    w = NLSClassify(c, cp == InputBuf, 0);
    switch(w) {
	case NLSCLASS_CTRL:
	    PutPlusOne('^', 1);
	    if (c == CTL_ESC('\177')) {
		PutPlusOne('?', 1);
		break;
	    }
#ifdef IS_ASCII
	    /* uncontrolify it; works only for iso8859-1 like sets */
	    PutPlusOne((c | 0100), 1);
#else
	    PutPlusOne(_toebcdic[_toascii[c]|0100], 1);
#endif
	    break;
	case NLSCLASS_ILLEGAL:
	    PutPlusOne('\\', 1);
	    PutPlusOne(((c >> 6) & 7) + '0', 1);
	    PutPlusOne(((c >> 3) & 7) + '0', 1);
	    PutPlusOne((c & 7) + '0', 1);
	    break;
	case 1:
	    if (adrof(STRhighlight) && MarkIsSet)
		StartHighlight();
	    if (l > 1)
		PutPlusOne(MakeLiteral(cp, l, 0), 1);
	    else
		PutPlusOne(*cp, 1);
	    if (adrof(STRhighlight) && MarkIsSet)
		StopHighlight();
	    break;
	default:
	    Refresh();		/* too hard to handle */
	    return;
    }
    flush();
}