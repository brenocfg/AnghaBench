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
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  cur_key ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int config_null_cb(void *params_) {
    if (!strcmp(cur_key, "id")) {
        /* If 'id' is NULL, the bar config was not found. Error out. */
        ELOG("No such bar config. Use 'i3-msg -t get_bar_config' to get the available configs.\n");
        ELOG("Are you starting i3bar by hand? You should not:\n");
        ELOG("Configure a 'bar' block in your i3 config and i3 will launch i3bar automatically.\n");
        exit(EXIT_FAILURE);
    }

    return 1;
}