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
struct TYPE_2__ {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmdbuf ; 
 int /*<<< orphan*/  cmdbuf_len ; 
 int /*<<< orphan*/  cmdbuf_pos ; 
 int /*<<< orphan*/  edit_clear_line () ; 
 int /*<<< orphan*/  edit_redraw () ; 
 TYPE_1__* history_curr ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void history_use(void)
{
	edit_clear_line();
	cmdbuf_len = cmdbuf_pos = os_strlen(history_curr->str);
	os_memcpy(cmdbuf, history_curr->str, cmdbuf_len);
	edit_redraw();
}