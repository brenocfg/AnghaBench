#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char wint_t ;
typedef  char wchar_t ;
typedef  size_t ssize_t ;
struct TYPE_8__ {int h; int v; } ;
struct TYPE_7__ {TYPE_2__ r_cursor; } ;
struct TYPE_9__ {TYPE_1__ el_refresh; } ;
typedef  TYPE_3__ EditLine ;

/* Variables and functions */
#define  CHTYPE_NL 130 
#define  CHTYPE_PRINT 129 
#define  CHTYPE_TAB 128 
 int VISUAL_WIDTH_MAX ; 
 int ct_chr_class (char) ; 
 size_t ct_visual_char (char*,int,char) ; 
 int /*<<< orphan*/  re_nextline (TYPE_3__*) ; 
 int /*<<< orphan*/  re_putc (TYPE_3__*,char,int) ; 

__attribute__((used)) static void
re_addc(EditLine *el, wint_t c)
{
	switch (ct_chr_class(c)) {
	case CHTYPE_TAB:        /* expand the tab */
		for (;;) {
			re_putc(el, ' ', 1);
			if ((el->el_refresh.r_cursor.h & 07) == 0)
				break;			/* go until tab stop */
		}
		break;
	case CHTYPE_NL: {
		int oldv = el->el_refresh.r_cursor.v;
		re_putc(el, '\0', 0);			/* assure end of line */
		if (oldv == el->el_refresh.r_cursor.v)	/* XXX */
			re_nextline(el);
		break;
	}
	case CHTYPE_PRINT:
		re_putc(el, c, 1);
		break;
	default: {
		wchar_t visbuf[VISUAL_WIDTH_MAX];
		ssize_t i, n =
		    ct_visual_char(visbuf, VISUAL_WIDTH_MAX, c);
		for (i = 0; n-- > 0; ++i)
		    re_putc(el, visbuf[i], 1);
		break;
	}
	}
}