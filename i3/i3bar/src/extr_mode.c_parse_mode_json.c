#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int yajl_status ;
typedef  int /*<<< orphan*/  yajl_handle ;
struct mode_json_params {char* json; int /*<<< orphan*/ * cur_key; TYPE_1__* mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ mode ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  I3STRING_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i3string_as_utf8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mode_callbacks ; 
 int /*<<< orphan*/  set_current_mode (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  yajl_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  yajl_free (int /*<<< orphan*/ ) ; 
 int yajl_parse (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
#define  yajl_status_client_canceled 130 
#define  yajl_status_error 129 
#define  yajl_status_ok 128 

void parse_mode_json(char *json) {
    /* FIXME: Fasciliate stream processing, i.e. allow starting to interpret
     * JSON in chunks */
    struct mode_json_params params;

    mode binding;

    params.cur_key = NULL;
    params.json = json;
    params.mode = &binding;

    yajl_handle handle;
    yajl_status state;

    handle = yajl_alloc(&mode_callbacks, NULL, (void *)&params);

    state = yajl_parse(handle, (const unsigned char *)json, strlen(json));

    /* FIXME: Proper error handling for JSON parsing */
    switch (state) {
        case yajl_status_ok:
            break;
        case yajl_status_client_canceled:
        case yajl_status_error:
            ELOG("Could not parse mode event!\n");
            exit(EXIT_FAILURE);
            break;
    }

    /* We don't want to indicate default binding mode */
    if (strcmp("default", i3string_as_utf8(params.mode->name)) == 0)
        I3STRING_FREE(params.mode->name);

    /* Set the new binding mode */
    set_current_mode(&binding);

    yajl_free(handle);

    FREE(params.cur_key);
}