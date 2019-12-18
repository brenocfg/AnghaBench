#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ws_num ;
struct workspaces_json_params {char* cur_key; TYPE_4__* workspaces_walk; } ;
struct TYPE_5__ {int /*<<< orphan*/  workspaces; } ;
typedef  TYPE_1__ i3_output ;
struct TYPE_7__ {scalar_t__ num; TYPE_1__* output; void* name; int /*<<< orphan*/  name_width; int /*<<< orphan*/  canonical_name; } ;
struct TYPE_6__ {scalar_t__ strip_ws_numbers; scalar_t__ strip_ws_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ config ; 
 TYPE_1__* get_output_by_name (char*) ; 
 int /*<<< orphan*/  i3string_as_utf8 (void*) ; 
 void* i3string_from_markup (char*) ; 
 void* i3string_from_markup_with_length (char const*,size_t) ; 
 int /*<<< orphan*/  i3string_get_num_glyphs (void*) ; 
 int /*<<< orphan*/  predict_text_width (void*) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,size_t,unsigned char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  sstrndup (char const*,size_t) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strspn (char const*,char*) ; 
 int /*<<< orphan*/  tailq ; 

__attribute__((used)) static int workspaces_string_cb(void *params_, const unsigned char *val, size_t len) {
    struct workspaces_json_params *params = (struct workspaces_json_params *)params_;

    if (!strcmp(params->cur_key, "name")) {
        const char *ws_name = (const char *)val;
        params->workspaces_walk->canonical_name = sstrndup(ws_name, len);

        if ((config.strip_ws_numbers || config.strip_ws_name) && params->workspaces_walk->num >= 0) {
            /* Special case: strip off the workspace number/name */
            static char ws_num[10];

            snprintf(ws_num, sizeof(ws_num), "%d", params->workspaces_walk->num);

            /* Calculate the length of the number str in the name */
            size_t offset = strspn(ws_name, ws_num);

            /* Also strip off the conventional ws name delimiter */
            if (offset && ws_name[offset] == ':')
                offset += 1;

            if (config.strip_ws_numbers) {
                /* Offset may be equal to length, in which case display the number */
                params->workspaces_walk->name = (offset < len
                                                     ? i3string_from_markup_with_length(ws_name + offset, len - offset)
                                                     : i3string_from_markup(ws_num));
            } else {
                params->workspaces_walk->name = i3string_from_markup(ws_num);
            }
        } else {
            /* Default case: just save the name */
            params->workspaces_walk->name = i3string_from_markup_with_length(ws_name, len);
        }

        /* Save its rendered width */
        params->workspaces_walk->name_width =
            predict_text_width(params->workspaces_walk->name);

        DLOG("Got workspace canonical: %s, name: '%s', name_width: %d, glyphs: %zu\n",
             params->workspaces_walk->canonical_name,
             i3string_as_utf8(params->workspaces_walk->name),
             params->workspaces_walk->name_width,
             i3string_get_num_glyphs(params->workspaces_walk->name));
        FREE(params->cur_key);

        return 1;
    }

    if (!strcmp(params->cur_key, "output")) {
        /* We add the ws to the TAILQ of the output, it belongs to */
        char *output_name = NULL;
        sasprintf(&output_name, "%.*s", len, val);

        i3_output *target = get_output_by_name(output_name);
        if (target != NULL) {
            params->workspaces_walk->output = target;

            TAILQ_INSERT_TAIL(params->workspaces_walk->output->workspaces,
                              params->workspaces_walk,
                              tailq);
        }

        FREE(output_name);
        return 1;
    }

    return 0;
}