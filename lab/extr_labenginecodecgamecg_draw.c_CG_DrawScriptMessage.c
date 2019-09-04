#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float member_0; float member_1; float member_2; float member_3; } ;
typedef  TYPE_1__ vec4_t ;

/* Variables and functions */
 scalar_t__ BIGCHAR_HEIGHT ; 
 int BIGCHAR_WIDTH ; 
 int /*<<< orphan*/  CG_DrawStringExt (int,int,char*,TYPE_1__,int /*<<< orphan*/ ,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int CG_DrawStrlen (char*) ; 
 int /*<<< orphan*/  SCREEN_HEIGHT ; 
 int /*<<< orphan*/  SCREEN_WIDTH ; 
 int /*<<< orphan*/  dmlab_get_screen_message (int,char*,int*,int*,int*,int*,TYPE_1__) ; 
 int dmlab_make_screen_messages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  qfalse ; 

__attribute__((used)) static void CG_DrawScriptMessage( void ) {
	char s[80];
	int c = 0;
	int i, x = 0, y = 0, align_l0_r1_c2 = 0;
	int shadow = 1;
	vec4_t rgba = {1.0f, 1.0f, 1.0f, 1.0f};
	c = dmlab_make_screen_messages(
			SCREEN_WIDTH, SCREEN_HEIGHT, BIGCHAR_HEIGHT + 4, 80 );
	for (i = 0; i < c; ++i) {
		dmlab_get_screen_message( i, s, &x, &y, &align_l0_r1_c2, &shadow, rgba );
		y = y + 2;
		switch (align_l0_r1_c2) {
			case 0:  // Left
				break;
			case 1:  // Right
				x -= CG_DrawStrlen( s ) * BIGCHAR_WIDTH;
				break;
			case 2:  // Center
			default:
				x -= CG_DrawStrlen( s ) * BIGCHAR_WIDTH / 2;
				break;
		}
		CG_DrawStringExt(
				x, y, s, rgba,
				/*forceColor=*/qfalse,
				/*shadow=*/shadow != 0,
				BIGCHAR_WIDTH, BIGCHAR_HEIGHT,
				/*maxChars=*/0 );
	}
}