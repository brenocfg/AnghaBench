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
typedef  int /*<<< orphan*/  qhandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CG_AdjustFrom640 (float*,float*,float*,float*) ; 
 int /*<<< orphan*/  trap_R_DrawStretchPic (float,float,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void CG_DrawPic( float x, float y, float width, float height, qhandle_t hShader ) {
	CG_AdjustFrom640( &x, &y, &width, &height );
	trap_R_DrawStretchPic( x, y, width, height, 0, 0, 1, 1, hShader );
}