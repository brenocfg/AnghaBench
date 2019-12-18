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
 int /*<<< orphan*/  DLOG (char*,int,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_CONTENT_WORKSPACE ; 
 int content_level ; 
 int /*<<< orphan*/  content_result ; 
 int /*<<< orphan*/  last_key ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncasecmp (char const*,char*,size_t) ; 

__attribute__((used)) static int json_determine_content_string(void *ctx, const unsigned char *val, size_t len) {
    if (strcasecmp(last_key, "type") != 0 || content_level > 1)
        return 1;

    DLOG("string = %.*s, last_key = %s\n", (int)len, val, last_key);
    if (strncasecmp((const char *)val, "workspace", len) == 0)
        content_result = JSON_CONTENT_WORKSPACE;
    return 0;
}