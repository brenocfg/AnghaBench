#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* pattern; } ;
struct TYPE_15__ {TYPE_1__ font; } ;
struct TYPE_14__ {int /*<<< orphan*/  command; } ;
struct TYPE_13__ {scalar_t__ parse_error; scalar_t__ needs_tree_render; } ;
typedef  int /*<<< orphan*/  Con ;
typedef  TYPE_2__ CommandResult ;
typedef  TYPE_3__ Binding ;

/* Variables and functions */
 TYPE_3__* binding_copy (TYPE_3__*) ; 
 int /*<<< orphan*/  binding_free (TYPE_3__*) ; 
 int /*<<< orphan*/  command_error_nagbar_pid ; 
 TYPE_8__ config ; 
 int /*<<< orphan*/  errorfilename ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ipc_send_binding_event (char*,TYPE_3__*) ; 
 TYPE_2__* parse_command (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,int /*<<< orphan*/ ,...) ; 
 char* sstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_nagbar (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  tree_render () ; 

CommandResult *run_binding(Binding *bind, Con *con) {
    char *command;

    /* We need to copy the binding and command since “reload” may be part of
     * the command, and then the memory that bind points to may not contain the
     * same data anymore. */
    if (con == NULL)
        command = sstrdup(bind->command);
    else
        sasprintf(&command, "[con_id=\"%p\"] %s", con, bind->command);

    Binding *bind_cp = binding_copy(bind);
    CommandResult *result = parse_command(command, NULL, NULL);
    free(command);

    if (result->needs_tree_render)
        tree_render();

    if (result->parse_error) {
        char *pageraction;
        sasprintf(&pageraction, "i3-sensible-pager \"%s\"\n", errorfilename);
        char *argv[] = {
            NULL, /* will be replaced by the executable path */
            "-f",
            config.font.pattern,
            "-t",
            "error",
            "-m",
            "The configured command for this shortcut could not be run successfully.",
            "-b",
            "show errors",
            pageraction,
            NULL};
        start_nagbar(&command_error_nagbar_pid, argv);
        free(pageraction);
    }

    ipc_send_binding_event("run", bind_cp);
    binding_free(bind_cp);

    return result;
}