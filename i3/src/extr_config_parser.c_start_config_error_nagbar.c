#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* pattern; } ;
struct TYPE_4__ {TYPE_1__ font; } ;

/* Variables and functions */
 TYPE_2__ config ; 
 int /*<<< orphan*/  config_error_nagbar_pid ; 
 char const* errorfilename ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  start_nagbar (int /*<<< orphan*/ *,char**) ; 

void start_config_error_nagbar(const char *configpath, bool has_errors) {
    char *editaction, *pageraction;
    sasprintf(&editaction, "i3-sensible-editor \"%s\" && i3-msg reload\n", configpath);
    sasprintf(&pageraction, "i3-sensible-pager \"%s\"\n", errorfilename);
    char *argv[] = {
        NULL, /* will be replaced by the executable path */
        "-f",
        (config.font.pattern ? config.font.pattern : "fixed"),
        "-t",
        (has_errors ? "error" : "warning"),
        "-m",
        (has_errors ? "You have an error in your i3 config file!" : "Your config is outdated. Please fix the warnings to make sure everything works."),
        "-b",
        "edit config",
        editaction,
        (errorfilename ? "-b" : NULL),
        (has_errors ? "show errors" : "show warnings"),
        pageraction,
        NULL};

    start_nagbar(&config_error_nagbar_pid, argv);
    free(editaction);
    free(pageraction);
}