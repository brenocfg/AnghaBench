#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int x; int y; int id; int flags; scalar_t__ name; } ;
struct TYPE_5__ {int width; int height; void* focusshader; TYPE_1__ generic; void* shader; scalar_t__ focuspic; scalar_t__ errorpic; } ;
typedef  TYPE_2__ menubitmap_s ;
struct TYPE_6__ {int page; int /*<<< orphan*/ * maplist; } ;

/* Variables and functions */
 int ID_PICTURES ; 
 int /*<<< orphan*/  Info_ValueForKey (char const*,char*) ; 
 int MAX_MAPSPERPAGE ; 
 int MAX_NAMELENGTH ; 
 int QMF_HIGHLIGHT ; 
 int /*<<< orphan*/  Q_strncpyz (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Q_strupr (char*) ; 
 int UI_CENTER ; 
 int /*<<< orphan*/  UI_DrawHandlePic (int,int,int,int,void*) ; 
 int /*<<< orphan*/  UI_DrawString (int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_FillRect (int,int,int,int,int /*<<< orphan*/ ) ; 
 char* UI_GetArenaInfoByNumber (int /*<<< orphan*/ ) ; 
 int UI_SMALLFONT ; 
 int /*<<< orphan*/  colorBlack ; 
 int /*<<< orphan*/  color_blue ; 
 TYPE_3__ s_startserver ; 
 void* trap_R_RegisterShaderNoMip (scalar_t__) ; 

__attribute__((used)) static void StartServer_LevelshotDraw( void *self ) {
	menubitmap_s	*b;
	int				x;
	int				y;
	int				w;
	int				h;
	int				n;
	const char		*info;
	char			mapname[ MAX_NAMELENGTH ];

	b = (menubitmap_s *)self;

	if( !b->generic.name ) {
		return;
	}

	if( b->generic.name && !b->shader ) {
		b->shader = trap_R_RegisterShaderNoMip( b->generic.name );
		if( !b->shader && b->errorpic ) {
			b->shader = trap_R_RegisterShaderNoMip( b->errorpic );
		}
	}

	if( b->focuspic && !b->focusshader ) {
		b->focusshader = trap_R_RegisterShaderNoMip( b->focuspic );
	}

	x = b->generic.x;
	y = b->generic.y;
	w = b->width;
	h =	b->height;
	if( b->shader ) {
		UI_DrawHandlePic( x, y, w, h, b->shader );
	}

	x = b->generic.x;
	y = b->generic.y + b->height;
	UI_FillRect( x, y, b->width, 28, colorBlack );

	x += b->width / 2;
	y += 4;
	n = s_startserver.page * MAX_MAPSPERPAGE + b->generic.id - ID_PICTURES;

	info = UI_GetArenaInfoByNumber( s_startserver.maplist[ n ]);
	Q_strncpyz( mapname, Info_ValueForKey( info, "map"), MAX_NAMELENGTH );
	Q_strupr( mapname );
	UI_DrawString( x, y, mapname, UI_CENTER|UI_SMALLFONT, color_blue );

	x = b->generic.x;
	y = b->generic.y;
	w = b->width;
	h =	b->height + 28;
	if( b->generic.flags & QMF_HIGHLIGHT ) {	
		UI_DrawHandlePic( x, y, w, h, b->focusshader );
	}
}