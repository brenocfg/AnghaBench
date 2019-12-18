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
 int /*<<< orphan*/  ewmh_update_current_desktop () ; 
 int /*<<< orphan*/  ewmh_update_desktop_names () ; 
 int /*<<< orphan*/  ewmh_update_desktop_viewport () ; 
 int /*<<< orphan*/  ewmh_update_number_of_desktops () ; 
 int /*<<< orphan*/  ewmh_update_wm_desktop () ; 

void ewmh_update_desktop_properties(void) {
    ewmh_update_number_of_desktops();
    ewmh_update_desktop_viewport();
    ewmh_update_current_desktop();
    ewmh_update_desktop_names();
    ewmh_update_wm_desktop();
}