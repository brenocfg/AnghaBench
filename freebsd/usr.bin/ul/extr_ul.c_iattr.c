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
struct TYPE_2__ {int c_mode; } ;

/* Variables and functions */
#define  ALTSET 133 
#define  BOLD 132 
#define  NORMAL 131 
#define  SUBSC 130 
#define  SUPERSC 129 
#define  UNDERL 128 
 int maxcol ; 
 TYPE_1__* obuf ; 
 int /*<<< orphan*/  putwchar (char) ; 

__attribute__((used)) static void
iattr(void)
{
	int i;
	wchar_t lbuf[256];
	wchar_t *cp = lbuf;

	for (i=0; i<maxcol; i++)
		switch (obuf[i].c_mode) {
		case NORMAL:	*cp++ = ' '; break;
		case ALTSET:	*cp++ = 'g'; break;
		case SUPERSC:	*cp++ = '^'; break;
		case SUBSC:	*cp++ = 'v'; break;
		case UNDERL:	*cp++ = '_'; break;
		case BOLD:	*cp++ = '!'; break;
		default:	*cp++ = 'X'; break;
		}
	for (*cp=' '; *cp==' '; cp--)
		*cp = 0;
	for (cp=lbuf; *cp; cp++)
		putwchar(*cp);
	putwchar('\n');
}