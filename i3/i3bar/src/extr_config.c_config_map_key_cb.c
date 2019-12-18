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
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cur_key ; 
 int parsing_bindings ; 
 int parsing_tray_outputs ; 
 int /*<<< orphan*/  sasprintf (int /*<<< orphan*/ *,char*,size_t,unsigned char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int config_map_key_cb(void *params_, const unsigned char *keyVal, size_t keyLen) {
    FREE(cur_key);
    sasprintf(&(cur_key), "%.*s", keyLen, keyVal);

    if (strcmp(cur_key, "bindings") == 0) {
        parsing_bindings = true;
    }

    if (strcmp(cur_key, "tray_outputs") == 0) {
        parsing_tray_outputs = true;
    }

    return 1;
}