#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct CommandResultIR {int needs_tree_render; } ;
struct TYPE_5__ {scalar_t__ workspace_auto_back_and_forth; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 TYPE_1__* con_get_workspace (int /*<<< orphan*/ ) ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/  focused ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  workspace_back_and_forth () ; 

__attribute__((used)) static bool maybe_back_and_forth(struct CommandResultIR *cmd_output, const char *name) {
    Con *ws = con_get_workspace(focused);

    /* If we switched to a different workspace, do nothing */
    if (strcmp(ws->name, name) != 0)
        return false;

    DLOG("This workspace is already focused.\n");
    if (config.workspace_auto_back_and_forth) {
        workspace_back_and_forth();
        cmd_output->needs_tree_render = true;
    }
    return true;
}