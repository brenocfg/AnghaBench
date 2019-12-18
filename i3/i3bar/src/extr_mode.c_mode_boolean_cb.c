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
struct mode_json_params {int pango_markup; int /*<<< orphan*/  cur_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mode_boolean_cb(void *params_, int val) {
    struct mode_json_params *params = (struct mode_json_params *)params_;

    if (strcmp(params->cur_key, "pango_markup") == 0) {
        DLOG("Setting pango_markup to %d.\n", val);
        params->pango_markup = val;

        FREE(params->cur_key);
        return 1;
    }

    FREE(params->cur_key);
    return 0;
}