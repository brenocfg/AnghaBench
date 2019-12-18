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
struct TYPE_3__ {char* name; int /*<<< orphan*/ * usage; } ;
typedef  TYPE_1__ SL_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ *,char const*) ; 

void
sl_apropos (SL_cmd *cmd, const char *topic)
{
    for (; cmd->name != NULL; ++cmd)
        if (cmd->usage != NULL && strstr(cmd->usage, topic) != NULL)
	    printf ("%-20s%s\n", cmd->name, cmd->usage);
}