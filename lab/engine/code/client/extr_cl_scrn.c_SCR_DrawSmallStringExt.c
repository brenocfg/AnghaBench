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
typedef  float* vec4_t ;
typedef  int /*<<< orphan*/  qboolean ;
typedef  int /*<<< orphan*/  color ;
struct TYPE_2__ {int /*<<< orphan*/  (* SetColor ) (float*) ;} ;

/* Variables and functions */
 size_t ColorIndex (char const) ; 
 int /*<<< orphan*/  Com_Memcpy (float*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ Q_IsColorString (char const*) ; 
 int /*<<< orphan*/  SCR_DrawSmallChar (int,int,char const) ; 
 scalar_t__ SMALLCHAR_WIDTH ; 
 int /*<<< orphan*/ * g_color_table ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (float*) ; 
 int /*<<< orphan*/  stub2 (float*) ; 
 int /*<<< orphan*/  stub3 (float*) ; 

void SCR_DrawSmallStringExt( int x, int y, const char *string, float *setColor, qboolean forceColor,
		qboolean noColorEscape ) {
	vec4_t		color;
	const char	*s;
	int			xx;

	// draw the colored text
	s = string;
	xx = x;
	re.SetColor( setColor );
	while ( *s ) {
		if ( Q_IsColorString( s ) ) {
			if ( !forceColor ) {
				Com_Memcpy( color, g_color_table[ColorIndex(*(s+1))], sizeof( color ) );
				color[3] = setColor[3];
				re.SetColor( color );
			}
			if ( !noColorEscape ) {
				s += 2;
				continue;
			}
		}
		SCR_DrawSmallChar( xx, y, *s );
		xx += SMALLCHAR_WIDTH;
		s++;
	}
	re.SetColor( NULL );
}