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
 int /*<<< orphan*/  ikbd_write (char*,int) ; 

void ikbd_mouse_pos_set(int x, int y)
{
	char cmd[6] = { 0x0E, 0x00, x>>8, x&0xFF, y>>8, y&0xFF };

	ikbd_write(cmd, 6);
}