#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_6__ {int event_x; int event_y; } ;
typedef  TYPE_1__ xcb_button_release_event_t ;
struct TYPE_7__ {char* action; scalar_t__ terminal; } ;
typedef  TYPE_2__ button_t ;
struct TYPE_8__ {scalar_t__ x; scalar_t__ width; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 char* argv0 ; 
 TYPE_5__ btn_close ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* get_button_at (scalar_t__,int) ; 
 char* get_exe_path (char*) ; 
 char* get_process_filename (char*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,char*) ; 
 char* sstrdup (char*) ; 
 int /*<<< orphan*/  start_application (char*) ; 
 int symlink (char*,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void handle_button_release(xcb_connection_t *conn, xcb_button_release_event_t *event) {
    printf("button released on x = %d, y = %d\n",
           event->event_x, event->event_y);
    /* If the user hits the close button, we exit(0) */
    if (event->event_x >= btn_close.x && event->event_x < btn_close.x + btn_close.width)
        exit(0);
    button_t *button = get_button_at(event->event_x, event->event_y);
    if (!button)
        return;

    /* We need to create a custom script containing our actual command
     * since not every terminal emulator which is contained in
     * i3-sensible-terminal supports -e with multiple arguments (and not
     * all of them support -e with one quoted argument either).
     *
     * NB: The paths need to be unique, that is, don’t assume users close
     * their nagbars at any point in time (and they still need to work).
     * */
    char *script_path = get_process_filename("nagbar-cmd");

    int fd = open(script_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        warn("Could not create temporary script to store the nagbar command");
        return;
    }
    FILE *script = fdopen(fd, "w");
    if (script == NULL) {
        warn("Could not fdopen() temporary script to store the nagbar command");
        return;
    }
    fprintf(script, "#!/bin/sh\nrm %s\n%s", script_path, button->action);
    /* Also closes fd */
    fclose(script);

    char *link_path;
    char *exe_path = get_exe_path(argv0);
    sasprintf(&link_path, "%s.nagbar_cmd", script_path);
    if (symlink(exe_path, link_path) == -1) {
        err(EXIT_FAILURE, "Failed to symlink %s to %s", link_path, exe_path);
    }

    char *terminal_cmd;
    if (button->terminal) {
        sasprintf(&terminal_cmd, "i3-sensible-terminal -e %s", link_path);
    } else {
        terminal_cmd = sstrdup(link_path);
    }
    printf("argv0 = %s\n", argv0);
    printf("terminal_cmd = %s\n", terminal_cmd);

    start_application(terminal_cmd);

    free(link_path);
    free(terminal_cmd);
    free(script_path);
    free(exe_path);

    /* TODO: unset flag, re-render */
}