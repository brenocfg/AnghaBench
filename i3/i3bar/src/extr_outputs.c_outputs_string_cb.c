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
struct outputs_json_params {char* cur_key; TYPE_1__* outputs_walk; } ;
struct TYPE_2__ {long ws; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  sasprintf (char**,char*,size_t,unsigned char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static int outputs_string_cb(void *params_, const unsigned char *val, size_t len) {
    struct outputs_json_params *params = (struct outputs_json_params *)params_;

    if (!strcmp(params->cur_key, "current_workspace")) {
        char *copy = NULL;
        sasprintf(&copy, "%.*s", len, val);

        char *end;
        errno = 0;
        long parsed_num = strtol(copy, &end, 10);
        if (errno == 0 &&
            (end && *end == '\0'))
            params->outputs_walk->ws = parsed_num;

        FREE(copy);
        FREE(params->cur_key);
        return 1;
    }

    if (strcmp(params->cur_key, "name")) {
        return 0;
    }

    sasprintf(&(params->outputs_walk->name), "%.*s", len, val);

    FREE(params->cur_key);
    return 1;
}