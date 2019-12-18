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
typedef  int yajl_status ;
typedef  int /*<<< orphan*/  yajl_handle ;
struct outputs_json_params {char* json; int in_rect; int /*<<< orphan*/ * cur_key; int /*<<< orphan*/ * outputs_walk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outputs_callbacks ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  yajl_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  yajl_free (int /*<<< orphan*/ ) ; 
 int yajl_parse (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
#define  yajl_status_client_canceled 130 
#define  yajl_status_error 129 
#define  yajl_status_ok 128 

void parse_outputs_json(char *json) {
    struct outputs_json_params params;
    params.outputs_walk = NULL;
    params.cur_key = NULL;
    params.json = json;
    params.in_rect = false;

    yajl_handle handle;
    yajl_status state;
    handle = yajl_alloc(&outputs_callbacks, NULL, (void *)&params);

    state = yajl_parse(handle, (const unsigned char *)json, strlen(json));

    /* FIXME: Proper errorhandling for JSON-parsing */
    switch (state) {
        case yajl_status_ok:
            break;
        case yajl_status_client_canceled:
        case yajl_status_error:
            ELOG("Could not parse outputs reply!\n");
            exit(EXIT_FAILURE);
            break;
    }

    yajl_free(handle);
}