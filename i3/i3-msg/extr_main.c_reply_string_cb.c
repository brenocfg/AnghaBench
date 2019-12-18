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
struct TYPE_2__ {char* error; char* input; char* errorposition; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  last_key ; 
 TYPE_1__ last_reply ; 
 char* sstrndup (char const*,size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int reply_string_cb(void *params, const unsigned char *val, size_t len) {
    char *str = sstrndup((const char *)val, len);

    if (strcmp(last_key, "error") == 0)
        last_reply.error = str;
    else if (strcmp(last_key, "input") == 0)
        last_reply.input = str;
    else if (strcmp(last_key, "errorposition") == 0)
        last_reply.errorposition = str;
    else
        free(str);
    return 1;
}