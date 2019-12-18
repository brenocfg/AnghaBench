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
typedef  int /*<<< orphan*/  SL_cmd ;

/* Variables and functions */
 int sl_command_loop (int /*<<< orphan*/ *,char const*,void**) ; 

int
sl_loop(SL_cmd *cmds, const char *prompt)
{
    void *data = NULL;
    int ret;
    while((ret = sl_command_loop(cmds, prompt, &data)) >= 0)
	;
    return ret;
}