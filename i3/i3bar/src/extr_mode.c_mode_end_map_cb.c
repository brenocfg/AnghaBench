#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mode_json_params {int /*<<< orphan*/  cur_key; TYPE_1__* mode; int /*<<< orphan*/  pango_markup; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  name_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3string_as_utf8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3string_from_utf8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3string_set_markup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  predict_text_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mode_end_map_cb(void *params_) {
    struct mode_json_params *params = (struct mode_json_params *)params_;

    /* Save the name */
    params->mode->name = i3string_from_utf8(params->name);
    i3string_set_markup(params->mode->name, params->pango_markup);
    /* Save its rendered width */
    params->mode->name_width = predict_text_width(params->mode->name);

    DLOG("Got mode change: %s\n", i3string_as_utf8(params->mode->name));
    FREE(params->cur_key);

    return 1;
}