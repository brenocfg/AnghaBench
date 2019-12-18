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
 size_t cmdbuf_len ; 
 scalar_t__ cmdbuf_pos ; 
 scalar_t__ currbuf_valid ; 
 int /*<<< orphan*/  edit_cb_ctx ; 
 int /*<<< orphan*/  edit_cmd_cb (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  history_add (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* ps2 ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void process_cmd(void)
{
	currbuf_valid = 0;
	if (cmdbuf_len == 0) {
		printf("\n%s> ", ps2 ? ps2 : "");
		fflush(stdout);
		return;
	}
	printf("\n");
	cmdbuf[cmdbuf_len] = '\0';
	history_add(cmdbuf);
	cmdbuf_pos = 0;
	cmdbuf_len = 0;
	edit_cmd_cb(edit_cb_ctx, cmdbuf);
	printf("%s> ", ps2 ? ps2 : "");
	fflush(stdout);
}