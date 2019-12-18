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
 char* cmdbuf ; 
 int cmdbuf_pos ; 
 int /*<<< orphan*/  edit_redraw () ; 

__attribute__((used)) static void move_word_left(void)
{
	while (cmdbuf_pos > 0 && cmdbuf[cmdbuf_pos - 1] == ' ')
		cmdbuf_pos--;
	while (cmdbuf_pos > 0 && cmdbuf[cmdbuf_pos - 1] != ' ')
		cmdbuf_pos--;
	edit_redraw();
}