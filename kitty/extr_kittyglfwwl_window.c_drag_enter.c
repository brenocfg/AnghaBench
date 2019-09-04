#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_surface {int dummy; } ;
struct wl_data_offer {int dummy; } ;
struct wl_data_device {int dummy; } ;
struct TYPE_4__ {TYPE_2__* dataOffers; } ;
struct TYPE_6__ {TYPE_1__ wl; } ;
struct TYPE_5__ {scalar_t__ offer_type; scalar_t__ has_uri_list; struct wl_surface* surface; struct wl_data_offer* id; } ;

/* Variables and functions */
 scalar_t__ DRAG_AND_DROP ; 
 scalar_t__ EXPIRED ; 
 char* URI_LIST_MIME ; 
 TYPE_3__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 
 int /*<<< orphan*/  prune_unclaimed_data_offers () ; 
 int /*<<< orphan*/  wl_data_offer_accept (struct wl_data_offer*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void drag_enter(void *data, struct wl_data_device *wl_data_device, uint32_t serial, struct wl_surface *surface, wl_fixed_t x, wl_fixed_t y, struct wl_data_offer *id) {
    for (size_t i = 0; i < arraysz(_glfw.wl.dataOffers); i++) {
        if (_glfw.wl.dataOffers[i].id == id) {
            _glfw.wl.dataOffers[i].offer_type = DRAG_AND_DROP;
            _glfw.wl.dataOffers[i].surface = surface;
            const char *mime = _glfw.wl.dataOffers[i].has_uri_list ? URI_LIST_MIME : NULL;
            wl_data_offer_accept(id, serial, mime);
        } else if (_glfw.wl.dataOffers[i].offer_type == DRAG_AND_DROP) {
            _glfw.wl.dataOffers[i].offer_type = EXPIRED;  // previous drag offer
        }
    }
    prune_unclaimed_data_offers();
}