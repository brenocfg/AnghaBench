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
 int /*<<< orphan*/  LOG (char*,int,unsigned char const*) ; 
 int /*<<< orphan*/  last_key ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 
 scalar_t__ num_marks ; 
 int parsing_deco_rect ; 
 int parsing_focus ; 
 int parsing_gaps ; 
 int parsing_geometry ; 
 int parsing_marks ; 
 int parsing_rect ; 
 int parsing_swallows ; 
 int parsing_window_rect ; 
 int /*<<< orphan*/  scalloc (size_t,int) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int json_key(void *ctx, const unsigned char *val, size_t len) {
    LOG("key: %.*s\n", (int)len, val);
    FREE(last_key);
    last_key = scalloc(len + 1, 1);
    memcpy(last_key, val, len);
    if (strcasecmp(last_key, "swallows") == 0)
        parsing_swallows = true;

    if (strcasecmp(last_key, "gaps") == 0)
        parsing_gaps = true;

    if (strcasecmp(last_key, "rect") == 0)
        parsing_rect = true;

    if (strcasecmp(last_key, "deco_rect") == 0)
        parsing_deco_rect = true;

    if (strcasecmp(last_key, "window_rect") == 0)
        parsing_window_rect = true;

    if (strcasecmp(last_key, "geometry") == 0)
        parsing_geometry = true;

    if (strcasecmp(last_key, "focus") == 0)
        parsing_focus = true;

    if (strcasecmp(last_key, "marks") == 0) {
        num_marks = 0;
        parsing_marks = true;
    }

    return 1;
}