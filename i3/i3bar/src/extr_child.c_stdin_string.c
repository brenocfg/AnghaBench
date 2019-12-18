#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pango_markup; int /*<<< orphan*/  instance; int /*<<< orphan*/  name; int /*<<< orphan*/  min_width_str; int /*<<< orphan*/  align; int /*<<< orphan*/  border; int /*<<< orphan*/  background; int /*<<< orphan*/  color; void* short_text; void* full_text; } ;
struct TYPE_4__ {TYPE_1__ block; int /*<<< orphan*/  last_map_key; } ;
typedef  TYPE_2__ parser_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN_CENTER ; 
 int /*<<< orphan*/  ALIGN_LEFT ; 
 int /*<<< orphan*/  ALIGN_RIGHT ; 
 void* i3string_from_markup_with_length (char const*,size_t) ; 
 int /*<<< orphan*/  sasprintf (int /*<<< orphan*/ *,char*,size_t,unsigned char const*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,size_t) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static int stdin_string(void *context, const unsigned char *val, size_t len) {
    parser_ctx *ctx = context;
    if (strcasecmp(ctx->last_map_key, "full_text") == 0) {
        ctx->block.full_text = i3string_from_markup_with_length((const char *)val, len);
        return 1;
    }
    if (strcasecmp(ctx->last_map_key, "short_text") == 0) {
        ctx->block.short_text = i3string_from_markup_with_length((const char *)val, len);
        return 1;
    }
    if (strcasecmp(ctx->last_map_key, "color") == 0) {
        sasprintf(&(ctx->block.color), "%.*s", len, val);
        return 1;
    }
    if (strcasecmp(ctx->last_map_key, "background") == 0) {
        sasprintf(&(ctx->block.background), "%.*s", len, val);
        return 1;
    }
    if (strcasecmp(ctx->last_map_key, "border") == 0) {
        sasprintf(&(ctx->block.border), "%.*s", len, val);
        return 1;
    }
    if (strcasecmp(ctx->last_map_key, "markup") == 0) {
        ctx->block.pango_markup = (len == strlen("pango") && !strncasecmp((const char *)val, "pango", strlen("pango")));
        return 1;
    }
    if (strcasecmp(ctx->last_map_key, "align") == 0) {
        if (len == strlen("center") && !strncmp((const char *)val, "center", strlen("center"))) {
            ctx->block.align = ALIGN_CENTER;
        } else if (len == strlen("right") && !strncmp((const char *)val, "right", strlen("right"))) {
            ctx->block.align = ALIGN_RIGHT;
        } else {
            ctx->block.align = ALIGN_LEFT;
        }
        return 1;
    }
    if (strcasecmp(ctx->last_map_key, "min_width") == 0) {
        sasprintf(&(ctx->block.min_width_str), "%.*s", len, val);
        return 1;
    }
    if (strcasecmp(ctx->last_map_key, "name") == 0) {
        sasprintf(&(ctx->block.name), "%.*s", len, val);
        return 1;
    }
    if (strcasecmp(ctx->last_map_key, "instance") == 0) {
        sasprintf(&(ctx->block.instance), "%.*s", len, val);
        return 1;
    }

    return 1;
}