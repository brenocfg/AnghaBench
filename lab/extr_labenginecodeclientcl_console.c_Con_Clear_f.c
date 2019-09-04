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
struct TYPE_2__ {int* text; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_WHITE ; 
 int CON_TEXTSIZE ; 
 int ColorIndex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Con_Bottom () ; 
 TYPE_1__ con ; 

void Con_Clear_f (void) {
	int		i;

	for ( i = 0 ; i < CON_TEXTSIZE ; i++ ) {
		con.text[i] = (ColorIndex(COLOR_WHITE)<<8) | ' ';
	}

	Con_Bottom();		// go to end
}