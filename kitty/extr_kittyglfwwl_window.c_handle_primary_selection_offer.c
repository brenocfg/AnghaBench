#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zwp_primary_selection_offer_v1 {int dummy; } ;
struct zwp_primary_selection_device_v1 {int dummy; } ;
struct TYPE_5__ {size_t primarySelectionOffersCounter; TYPE_2__* primarySelectionOffers; } ;
struct TYPE_7__ {TYPE_1__ wl; } ;
struct TYPE_6__ {size_t idx; struct zwp_primary_selection_offer_v1* id; } ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 TYPE_4__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  primary_selection_offer_listener ; 
 int /*<<< orphan*/  zwp_primary_selection_offer_v1_add_listener (struct zwp_primary_selection_offer_v1*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zwp_primary_selection_offer_v1_destroy (struct zwp_primary_selection_offer_v1*) ; 

__attribute__((used)) static void handle_primary_selection_offer(void *data, struct zwp_primary_selection_device_v1 *zwp_primary_selection_device_v1, struct zwp_primary_selection_offer_v1 *id) {
    size_t smallest_idx = SIZE_MAX, pos = 0;
    for (size_t i = 0; i < arraysz(_glfw.wl.primarySelectionOffers); i++) {
        if (_glfw.wl.primarySelectionOffers[i].idx && _glfw.wl.primarySelectionOffers[i].idx < smallest_idx) {
            smallest_idx = _glfw.wl.primarySelectionOffers[i].idx;
            pos = i;
        }
        if (_glfw.wl.primarySelectionOffers[i].id == NULL) {
            _glfw.wl.primarySelectionOffers[i].id = id;
            _glfw.wl.primarySelectionOffers[i].idx = ++_glfw.wl.primarySelectionOffersCounter;
            goto end;
        }
    }
    if (_glfw.wl.primarySelectionOffers[pos].id) zwp_primary_selection_offer_v1_destroy(_glfw.wl.primarySelectionOffers[pos].id);
    memset(_glfw.wl.primarySelectionOffers + pos, 0, sizeof(_glfw.wl.primarySelectionOffers[0]));
    _glfw.wl.primarySelectionOffers[pos].id = id;
    _glfw.wl.primarySelectionOffers[pos].idx = ++_glfw.wl.primarySelectionOffersCounter;
end:
    zwp_primary_selection_offer_v1_add_listener(id, &primary_selection_offer_listener, NULL);
}