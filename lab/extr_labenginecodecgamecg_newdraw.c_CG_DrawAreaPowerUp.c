#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec4_t ;
struct TYPE_9__ {float x; float y; double w; float h; } ;
typedef  TYPE_2__ rectDef_t ;
struct TYPE_10__ {scalar_t__* stats; int* powerups; } ;
typedef  TYPE_3__ playerState_t ;
typedef  int /*<<< orphan*/  num ;
struct TYPE_11__ {int /*<<< orphan*/  icon; } ;
typedef  TYPE_4__ gitem_t ;
struct TYPE_12__ {int time; TYPE_1__* snap; } ;
struct TYPE_8__ {TYPE_3__ ps; } ;

/* Variables and functions */
 TYPE_4__* BG_FindItemForPowerup (int) ; 
 int /*<<< orphan*/  CG_DrawPic (float,float,double,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CG_Text_Paint (float,float,float,float*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,int) ; 
 int HUD_VERTICAL ; 
 int INT_MAX ; 
 int MAX_POWERUPS ; 
 int POWERUP_BLINKS ; 
 int POWERUP_BLINK_TIME ; 
 size_t STAT_HEALTH ; 
 TYPE_5__ cg ; 
 int /*<<< orphan*/  trap_R_RegisterShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_R_SetColor (float*) ; 

__attribute__((used)) static void CG_DrawAreaPowerUp(rectDef_t *rect, int align, float special, float scale, vec4_t color) {
	char num[16];
	int		sorted[MAX_POWERUPS];
	int		sortedTime[MAX_POWERUPS];
	int		i, j, k;
	int		active;
	playerState_t	*ps;
	int		t;
	gitem_t	*item;
	float	f;
	rectDef_t r2;
	float *inc;
	r2.x = rect->x;
	r2.y = rect->y;
	r2.w = rect->w;
	r2.h = rect->h;

	inc = (align == HUD_VERTICAL) ? &r2.y : &r2.x;

	ps = &cg.snap->ps;

	if ( ps->stats[STAT_HEALTH] <= 0 ) {
		return;
	}

	// sort the list by time remaining
	active = 0;
	for ( i = 0 ; i < MAX_POWERUPS ; i++ ) {
		if ( !ps->powerups[ i ] ) {
			continue;
		}

		// ZOID--don't draw if the power up has unlimited time
		// This is true of the CTF flags
		if ( ps->powerups[ i ] == INT_MAX ) {
			continue;
		}

		t = ps->powerups[ i ] - cg.time;
		if ( t <= 0 ) {
			continue;
		}

		// insert into the list
		for ( j = 0 ; j < active ; j++ ) {
			if ( sortedTime[j] >= t ) {
				for ( k = active - 1 ; k >= j ; k-- ) {
					sorted[k+1] = sorted[k];
					sortedTime[k+1] = sortedTime[k];
				}
				break;
			}
		}
		sorted[j] = i;
		sortedTime[j] = t;
		active++;
	}

	// draw the icons and timers
	for ( i = 0 ; i < active ; i++ ) {
		item = BG_FindItemForPowerup( sorted[i] );

		if (item) {
			t = ps->powerups[ sorted[i] ];
			if ( t - cg.time >= POWERUP_BLINKS * POWERUP_BLINK_TIME ) {
				trap_R_SetColor( NULL );
			} else {
				vec4_t	modulate;

				f = (float)( t - cg.time ) / POWERUP_BLINK_TIME;
				f -= (int)f;
				modulate[0] = modulate[1] = modulate[2] = modulate[3] = f;
				trap_R_SetColor( modulate );
			}

			CG_DrawPic( r2.x, r2.y, r2.w * .75, r2.h, trap_R_RegisterShader( item->icon ) );

			Com_sprintf (num, sizeof(num), "%i", sortedTime[i] / 1000);
			CG_Text_Paint(r2.x + (r2.w * .75) + 3 , r2.y + r2.h, scale, color, num, 0, 0, 0);
			*inc += r2.w + special;
		}

	}
	trap_R_SetColor( NULL );

}