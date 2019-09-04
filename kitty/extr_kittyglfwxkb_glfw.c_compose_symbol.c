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
typedef  scalar_t__ xkb_keysym_t ;
struct xkb_compose_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  text; } ;

/* Variables and functions */
#define  XKB_COMPOSE_CANCELLED 131 
#define  XKB_COMPOSE_COMPOSED 130 
#define  XKB_COMPOSE_COMPOSING 129 
 scalar_t__ XKB_COMPOSE_FEED_ACCEPTED ; 
#define  XKB_COMPOSE_NOTHING 128 
 scalar_t__ XKB_KEY_NoSymbol ; 
 TYPE_1__ key_event ; 
 scalar_t__ xkb_compose_state_feed (struct xkb_compose_state*,scalar_t__) ; 
 scalar_t__ xkb_compose_state_get_one_sym (struct xkb_compose_state*) ; 
 int xkb_compose_state_get_status (struct xkb_compose_state*) ; 
 int /*<<< orphan*/  xkb_compose_state_get_utf8 (struct xkb_compose_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline xkb_keysym_t
compose_symbol(struct xkb_compose_state *composeState, xkb_keysym_t sym, int *compose_completed) {
    *compose_completed = 0;
    if (sym == XKB_KEY_NoSymbol || !composeState) return sym;
    if (xkb_compose_state_feed(composeState, sym) != XKB_COMPOSE_FEED_ACCEPTED) return sym;
    switch (xkb_compose_state_get_status(composeState)) {
        case XKB_COMPOSE_COMPOSED:
            xkb_compose_state_get_utf8(composeState, key_event.text, sizeof(key_event.text));
            *compose_completed = 1;
            return xkb_compose_state_get_one_sym(composeState);
        case XKB_COMPOSE_COMPOSING:
        case XKB_COMPOSE_CANCELLED:
            return XKB_KEY_NoSymbol;
        case XKB_COMPOSE_NOTHING:
        default:
            return sym;
    }
}