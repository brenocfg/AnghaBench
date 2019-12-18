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
 scalar_t__ cmdbuf ; 
 scalar_t__ cmdbuf_len ; 
 scalar_t__ cmdbuf_pos ; 
 int /*<<< orphan*/  edit_clear_line () ; 
 int /*<<< orphan*/  edit_redraw () ; 
 int /*<<< orphan*/  os_memmove (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void delete_current(void)
{
	if (cmdbuf_pos == cmdbuf_len)
		return;

	edit_clear_line();
	os_memmove(cmdbuf + cmdbuf_pos, cmdbuf + cmdbuf_pos + 1,
		   cmdbuf_len - cmdbuf_pos);
	cmdbuf_len--;
	edit_redraw();
}