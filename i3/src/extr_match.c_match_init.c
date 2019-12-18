#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  window_type; int /*<<< orphan*/  window_mode; int /*<<< orphan*/  urgent; } ;
typedef  TYPE_1__ Match ;

/* Variables and functions */
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  U_DONTCHECK ; 
 int /*<<< orphan*/  WM_ANY ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void match_init(Match *match) {
    memset(match, 0, sizeof(Match));
    match->urgent = U_DONTCHECK;
    match->window_mode = WM_ANY;
    /* we use this as the placeholder value for "not set". */
    match->window_type = UINT32_MAX;
}