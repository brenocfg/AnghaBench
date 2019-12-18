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
struct TYPE_3__ {scalar_t__ urgent; scalar_t__ id; scalar_t__ window_type; scalar_t__ dock; scalar_t__ window_mode; int /*<<< orphan*/ * con_id; int /*<<< orphan*/ * workspace; int /*<<< orphan*/ * window_role; int /*<<< orphan*/ * instance; int /*<<< orphan*/ * class; int /*<<< orphan*/ * application; int /*<<< orphan*/ * mark; int /*<<< orphan*/ * title; } ;
typedef  TYPE_1__ Match ;

/* Variables and functions */
 scalar_t__ M_NODOCK ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ U_DONTCHECK ; 
 scalar_t__ WM_ANY ; 
 scalar_t__ XCB_NONE ; 

bool match_is_empty(Match *match) {
    /* we cannot simply use memcmp() because the structure is part of a
     * TAILQ and I don’t want to start with things like assuming that the
     * last member of a struct really is at the end in memory… */
    return (match->title == NULL &&
            match->mark == NULL &&
            match->application == NULL &&
            match->class == NULL &&
            match->instance == NULL &&
            match->window_role == NULL &&
            match->workspace == NULL &&
            match->urgent == U_DONTCHECK &&
            match->id == XCB_NONE &&
            match->window_type == UINT32_MAX &&
            match->con_id == NULL &&
            match->dock == M_NODOCK &&
            match->window_mode == WM_ANY);
}