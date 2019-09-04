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
typedef  double* vec4_t ;
struct TYPE_2__ {int realtime; } ;

/* Variables and functions */
 int BIGCHAR_HEIGHT ; 
 int BIGCHAR_WIDTH ; 
 int BLINK_DIVISOR ; 
 int GIANTCHAR_HEIGHT ; 
 int GIANTCHAR_WIDTH ; 
 int PULSE_DIVISOR ; 
 int SMALLCHAR_HEIGHT ; 
 int SMALLCHAR_WIDTH ; 
 int UI_BLINK ; 
#define  UI_CENTER 129 
 int UI_DROPSHADOW ; 
 int /*<<< orphan*/  UI_DrawString2 (int,int,char const*,...) ; 
 int UI_FORMATMASK ; 
 int UI_GIANTFONT ; 
 int /*<<< orphan*/  UI_LerpColor (double*,double*,double*,double) ; 
 int UI_PULSE ; 
#define  UI_RIGHT 128 
 int UI_SMALLFONT ; 
 double sin (int) ; 
 int strlen (char const*) ; 
 TYPE_1__ uis ; 

void UI_DrawString( int x, int y, const char* str, int style, vec4_t color )
{
	int		len;
	int		charw;
	int		charh;
	vec4_t	newcolor;
	vec4_t	lowlight;
	float	*drawcolor;
	vec4_t	dropcolor;

	if( !str ) {
		return;
	}

	if ((style & UI_BLINK) && ((uis.realtime/BLINK_DIVISOR) & 1))
		return;

	if (style & UI_SMALLFONT)
	{
		charw =	SMALLCHAR_WIDTH;
		charh =	SMALLCHAR_HEIGHT;
	}
	else if (style & UI_GIANTFONT)
	{
		charw =	GIANTCHAR_WIDTH;
		charh =	GIANTCHAR_HEIGHT;
	}
	else
	{
		charw =	BIGCHAR_WIDTH;
		charh =	BIGCHAR_HEIGHT;
	}

	if (style & UI_PULSE)
	{
		lowlight[0] = 0.8*color[0]; 
		lowlight[1] = 0.8*color[1];
		lowlight[2] = 0.8*color[2];
		lowlight[3] = 0.8*color[3];
		UI_LerpColor(color,lowlight,newcolor,0.5+0.5*sin(uis.realtime/PULSE_DIVISOR));
		drawcolor = newcolor;
	}	
	else
		drawcolor = color;

	switch (style & UI_FORMATMASK)
	{
		case UI_CENTER:
			// center justify at x
			len = strlen(str);
			x   = x - len*charw/2;
			break;

		case UI_RIGHT:
			// right justify at x
			len = strlen(str);
			x   = x - len*charw;
			break;

		default:
			// left justify at x
			break;
	}

	if ( style & UI_DROPSHADOW )
	{
		dropcolor[0] = dropcolor[1] = dropcolor[2] = 0;
		dropcolor[3] = drawcolor[3];
		UI_DrawString2(x+2,y+2,str,dropcolor,charw,charh);
	}

	UI_DrawString2(x,y,str,drawcolor,charw,charh);
}