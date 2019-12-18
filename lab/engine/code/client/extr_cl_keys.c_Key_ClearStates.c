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
struct TYPE_2__ {scalar_t__ repeats; scalar_t__ down; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_KeyEvent (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_KEYS ; 
 scalar_t__ anykeydown ; 
 TYPE_1__* keys ; 
 int /*<<< orphan*/  qfalse ; 

void Key_ClearStates (void)
{
	int		i;

	anykeydown = 0;

	for ( i=0 ; i < MAX_KEYS ; i++ ) {
		if ( keys[i].down ) {
			CL_KeyEvent( i, qfalse, 0 );

		}
		keys[i].down = 0;
		keys[i].repeats = 0;
	}
}