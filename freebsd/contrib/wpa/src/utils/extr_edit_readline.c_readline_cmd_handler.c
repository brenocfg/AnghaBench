#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ HIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  add_history (char*) ; 
 int /*<<< orphan*/  edit_cb_ctx ; 
 int /*<<< orphan*/  edit_cmd_cb (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edit_eof_cb (int /*<<< orphan*/ ) ; 
 scalar_t__ next_history () ; 
 scalar_t__ os_strcmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* previous_history () ; 
 int /*<<< orphan*/  trunc_nl (char*) ; 

__attribute__((used)) static void readline_cmd_handler(char *cmd)
{
	if (cmd && *cmd) {
		HIST_ENTRY *h;
		while (next_history())
			;
		h = previous_history();
		if (h == NULL || os_strcmp(cmd, h->line) != 0)
			add_history(cmd);
		next_history();
	}
	if (cmd == NULL) {
		edit_eof_cb(edit_cb_ctx);
		return;
	}
	trunc_nl(cmd);
	edit_cmd_cb(edit_cb_ctx, cmd);
}