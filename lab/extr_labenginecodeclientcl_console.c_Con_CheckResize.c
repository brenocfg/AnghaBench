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
struct TYPE_2__ {int linewidth; int totallines; int* text; int current; int display; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_WHITE ; 
 int CON_TEXTSIZE ; 
 int ColorIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Memcpy (short*,int*,int) ; 
 int /*<<< orphan*/  Con_ClearNotify () ; 
 int DEFAULT_CONSOLE_WIDTH ; 
 int SCREEN_WIDTH ; 
 int SMALLCHAR_WIDTH ; 
 TYPE_1__ con ; 

void Con_CheckResize (void)
{
	int		i, j, width, oldwidth, oldtotallines, numlines, numchars;
	short	tbuf[CON_TEXTSIZE];

	width = (SCREEN_WIDTH / SMALLCHAR_WIDTH) - 2;

	if (width == con.linewidth)
		return;

	if (width < 1)			// video hasn't been initialized yet
	{
		width = DEFAULT_CONSOLE_WIDTH;
		con.linewidth = width;
		con.totallines = CON_TEXTSIZE / con.linewidth;
		for(i=0; i<CON_TEXTSIZE; i++)

			con.text[i] = (ColorIndex(COLOR_WHITE)<<8) | ' ';
	}
	else
	{
		oldwidth = con.linewidth;
		con.linewidth = width;
		oldtotallines = con.totallines;
		con.totallines = CON_TEXTSIZE / con.linewidth;
		numlines = oldtotallines;

		if (con.totallines < numlines)
			numlines = con.totallines;

		numchars = oldwidth;
	
		if (con.linewidth < numchars)
			numchars = con.linewidth;

		Com_Memcpy (tbuf, con.text, CON_TEXTSIZE * sizeof(short));
		for(i=0; i<CON_TEXTSIZE; i++)

			con.text[i] = (ColorIndex(COLOR_WHITE)<<8) | ' ';


		for (i=0 ; i<numlines ; i++)
		{
			for (j=0 ; j<numchars ; j++)
			{
				con.text[(con.totallines - 1 - i) * con.linewidth + j] =
						tbuf[((con.current - i + oldtotallines) %
							  oldtotallines) * oldwidth + j];
			}
		}

		Con_ClearNotify ();
	}

	con.current = con.totallines - 1;
	con.display = con.current;
}