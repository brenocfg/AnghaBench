#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  whiteShader; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* SetColor ) (float const*) ;int /*<<< orphan*/  (* DrawStretchPic ) (float,float,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SCR_AdjustFrom640 (float*,float*,float*,float*) ; 
 TYPE_2__ cls ; 
 TYPE_1__ re ; 
 int /*<<< orphan*/  stub1 (float const*) ; 
 int /*<<< orphan*/  stub2 (float,float,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (float const*) ; 

void SCR_FillRect( float x, float y, float width, float height, const float *color ) {
	re.SetColor( color );

	SCR_AdjustFrom640( &x, &y, &width, &height );
	re.DrawStretchPic( x, y, width, height, 0, 0, 0, 0, cls.whiteShader );

	re.SetColor( NULL );
}