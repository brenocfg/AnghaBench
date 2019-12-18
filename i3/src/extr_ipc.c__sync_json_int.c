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
typedef  scalar_t__ xcb_window_t ;
struct sync_state {long long rnd; scalar_t__ window; int /*<<< orphan*/  last_key; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int _sync_json_int(void *extra, long long val) {
    struct sync_state *state = extra;
    if (strcasecmp(state->last_key, "rnd") == 0) {
        state->rnd = val;
    } else if (strcasecmp(state->last_key, "window") == 0) {
        state->window = (xcb_window_t)val;
    }
    return 1;
}