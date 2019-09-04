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
struct wl_data_offer {int dummy; } ;
struct wl_data_device {int dummy; } ;
struct TYPE_5__ {size_t dataOffersCounter; TYPE_2__* dataOffers; } ;
struct TYPE_7__ {TYPE_1__ wl; } ;
struct TYPE_6__ {size_t idx; struct wl_data_offer* id; } ;

/* Variables and functions */
 size_t SIZE_MAX ; 
 TYPE_4__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 
 int /*<<< orphan*/  data_offer_listener ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl_data_offer_add_listener (struct wl_data_offer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_data_offer_destroy (struct wl_data_offer*) ; 

__attribute__((used)) static void handle_data_offer(void *data, struct wl_data_device *wl_data_device, struct wl_data_offer *id) {
    size_t smallest_idx = SIZE_MAX, pos = 0;
    for (size_t i = 0; i < arraysz(_glfw.wl.dataOffers); i++) {
        if (_glfw.wl.dataOffers[i].idx && _glfw.wl.dataOffers[i].idx < smallest_idx) {
            smallest_idx = _glfw.wl.dataOffers[i].idx;
            pos = i;
        }
        if (_glfw.wl.dataOffers[i].id == NULL) {
            _glfw.wl.dataOffers[i].id = id;
            _glfw.wl.dataOffers[i].idx = ++_glfw.wl.dataOffersCounter;
            goto end;
        }
    }
    if (_glfw.wl.dataOffers[pos].id) wl_data_offer_destroy(_glfw.wl.dataOffers[pos].id);
    memset(_glfw.wl.dataOffers + pos, 0, sizeof(_glfw.wl.dataOffers[0]));
    _glfw.wl.dataOffers[pos].id = id;
    _glfw.wl.dataOffers[pos].idx = ++_glfw.wl.dataOffersCounter;
end:
    wl_data_offer_add_listener(id, &data_offer_listener, NULL);
}