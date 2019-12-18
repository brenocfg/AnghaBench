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
struct mode_json_params {int /*<<< orphan*/  cur_key; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sasprintf (int /*<<< orphan*/ *,char*,size_t,unsigned char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mode_string_cb(void *params_, const unsigned char *val, size_t len) {
    struct mode_json_params *params = (struct mode_json_params *)params_;

    if (!strcmp(params->cur_key, "change")) {
        sasprintf(&(params->name), "%.*s", len, val);
        FREE(params->cur_key);
        return 1;
    }

    FREE(params->cur_key);
    return 0;
}