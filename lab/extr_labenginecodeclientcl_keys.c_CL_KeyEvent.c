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
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 int /*<<< orphan*/  CL_KeyDownEvent (int,unsigned int) ; 
 int /*<<< orphan*/  CL_KeyUpEvent (int,unsigned int) ; 

void CL_KeyEvent (int key, qboolean down, unsigned time) {
	if( down )
		CL_KeyDownEvent( key, time );
	else
		CL_KeyUpEvent( key, time );
}