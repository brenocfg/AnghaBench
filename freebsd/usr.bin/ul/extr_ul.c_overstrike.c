#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct TYPE_2__ {int c_mode; int c_width; int /*<<< orphan*/  c_char; } ;

/* Variables and functions */
#define  BOLD 130 
#define  NORMAL 129 
#define  UNDERL 128 
 int maxcol ; 
 TYPE_1__* obuf ; 
 int /*<<< orphan*/  putwchar (char) ; 

__attribute__((used)) static void
overstrike(void)
{
	int i;
	wchar_t lbuf[256];
	wchar_t *cp = lbuf;
	int hadbold=0;

	/* Set up overstrike buffer */
	for (i=0; i<maxcol; i++)
		switch (obuf[i].c_mode) {
		case NORMAL:
		default:
			*cp++ = ' ';
			break;
		case UNDERL:
			*cp++ = '_';
			break;
		case BOLD:
			*cp++ = obuf[i].c_char;
			if (obuf[i].c_width > 1)
				i += obuf[i].c_width - 1;
			hadbold=1;
			break;
		}
	putwchar('\r');
	for (*cp=' '; *cp==' '; cp--)
		*cp = 0;
	for (cp=lbuf; *cp; cp++)
		putwchar(*cp);
	if (hadbold) {
		putwchar('\r');
		for (cp=lbuf; *cp; cp++)
			putwchar(*cp=='_' ? ' ' : *cp);
		putwchar('\r');
		for (cp=lbuf; *cp; cp++)
			putwchar(*cp=='_' ? ' ' : *cp);
	}
}