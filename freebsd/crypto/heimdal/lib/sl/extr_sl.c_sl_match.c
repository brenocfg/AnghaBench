#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ name; scalar_t__ func; } ;
typedef  TYPE_1__ SL_cmd ;

/* Variables and functions */
 scalar_t__ strcmp (char*,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,scalar_t__,int /*<<< orphan*/ ) ; 

SL_cmd *
sl_match (SL_cmd *cmds, char *cmd, int exactp)
{
    SL_cmd *c, *current = NULL, *partial_cmd = NULL;
    int partial_match = 0;

    for (c = cmds; c->name; ++c) {
	if (c->func)
	    current = c;
	if (strcmp (cmd, c->name) == 0)
	    return current;
	else if (strncmp (cmd, c->name, strlen(cmd)) == 0 &&
		 partial_cmd != current) {
	    ++partial_match;
	    partial_cmd = current;
	}
    }
    if (partial_match == 1 && !exactp)
	return partial_cmd;
    else
	return NULL;
}