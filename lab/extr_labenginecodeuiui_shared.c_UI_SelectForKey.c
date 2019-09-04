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

/* Variables and functions */
#define  K_ENTER 140 
#define  K_JOY1 139 
#define  K_JOY2 138 
#define  K_JOY3 137 
#define  K_JOY4 136 
#define  K_KP_ENTER 135 
#define  K_KP_LEFTARROW 134 
#define  K_KP_RIGHTARROW 133 
#define  K_LEFTARROW 132 
#define  K_MOUSE1 131 
#define  K_MOUSE2 130 
#define  K_MOUSE3 129 
#define  K_RIGHTARROW 128 

int UI_SelectForKey(int key)
{
	switch (key) {
		case K_MOUSE1:
		case K_MOUSE3:
		case K_ENTER:
		case K_KP_ENTER:
		case K_RIGHTARROW:
		case K_KP_RIGHTARROW:
		case K_JOY1:
		case K_JOY2:
		case K_JOY3:
		case K_JOY4:
			return 1; // next

		case K_MOUSE2:
		case K_LEFTARROW:
		case K_KP_LEFTARROW:
			return -1; // previous
	}

	// no change
	return 0;
}