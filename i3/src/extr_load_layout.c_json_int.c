#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct focus_mapping {long long old_id; } ;
struct TYPE_8__ {long long id; long long dock; long long insert_where; } ;
struct TYPE_5__ {long long inner; long long top; long long right; long long bottom; long long left; } ;
struct TYPE_6__ {long long x; long long y; long long width; long long height; } ;
struct TYPE_7__ {long long type; long long fullscreen_mode; long long num; long long current_border_width; long long depth; long long old_id; TYPE_1__ gaps; TYPE_2__ geometry; TYPE_2__ window_rect; TYPE_2__ rect; } ;
typedef  TYPE_2__ Rect ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,long long,long long,long long,long long) ; 
 int /*<<< orphan*/  ELOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG (char*,long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct focus_mapping*,int /*<<< orphan*/ ) ; 
 TYPE_4__* current_swallow ; 
 int /*<<< orphan*/  focus_mappings ; 
 TYPE_3__* json_node ; 
 int /*<<< orphan*/  last_key ; 
 scalar_t__ parsing_focus ; 
 scalar_t__ parsing_gaps ; 
 scalar_t__ parsing_geometry ; 
 scalar_t__ parsing_rect ; 
 scalar_t__ parsing_swallows ; 
 scalar_t__ parsing_window_rect ; 
 struct focus_mapping* scalloc (int,int) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int swallow_is_empty ; 

__attribute__((used)) static int json_int(void *ctx, long long val) {
    LOG("int %lld for key %s\n", val, last_key);
    /* For backwards compatibility with i3 < 4.8 */
    if (strcasecmp(last_key, "type") == 0)
        json_node->type = val;

    if (strcasecmp(last_key, "fullscreen_mode") == 0)
        json_node->fullscreen_mode = val;

    if (strcasecmp(last_key, "num") == 0)
        json_node->num = val;

    if (strcasecmp(last_key, "current_border_width") == 0)
        json_node->current_border_width = val;

    if (strcasecmp(last_key, "depth") == 0)
        json_node->depth = val;

    if (!parsing_swallows && strcasecmp(last_key, "id") == 0)
        json_node->old_id = val;

    if (parsing_focus) {
        struct focus_mapping *focus_mapping = scalloc(1, sizeof(struct focus_mapping));
        focus_mapping->old_id = val;
        TAILQ_INSERT_TAIL(&focus_mappings, focus_mapping, focus_mappings);
    }

    if (parsing_rect || parsing_window_rect || parsing_geometry) {
        Rect *r;
        if (parsing_rect)
            r = &(json_node->rect);
        else if (parsing_window_rect)
            r = &(json_node->window_rect);
        else
            r = &(json_node->geometry);
        if (strcasecmp(last_key, "x") == 0)
            r->x = val;
        else if (strcasecmp(last_key, "y") == 0)
            r->y = val;
        else if (strcasecmp(last_key, "width") == 0)
            r->width = val;
        else if (strcasecmp(last_key, "height") == 0)
            r->height = val;
        else
            ELOG("WARNING: unknown key %s in rect\n", last_key);
        DLOG("rect now: (%d, %d, %d, %d)\n",
             r->x, r->y, r->width, r->height);
    }
    if (parsing_swallows) {
        if (strcasecmp(last_key, "id") == 0) {
            current_swallow->id = val;
            swallow_is_empty = false;
        }
        if (strcasecmp(last_key, "dock") == 0) {
            current_swallow->dock = val;
            swallow_is_empty = false;
        }
        if (strcasecmp(last_key, "insert_where") == 0) {
            current_swallow->insert_where = val;
            swallow_is_empty = false;
        }
    }
    if (parsing_gaps) {
        if (strcasecmp(last_key, "inner") == 0)
            json_node->gaps.inner = val;
        else if (strcasecmp(last_key, "top") == 0)
            json_node->gaps.top = val;
        else if (strcasecmp(last_key, "right") == 0)
            json_node->gaps.right = val;
        else if (strcasecmp(last_key, "bottom") == 0)
            json_node->gaps.bottom = val;
        else if (strcasecmp(last_key, "left") == 0)
            json_node->gaps.left = val;
    }

    return 1;
}