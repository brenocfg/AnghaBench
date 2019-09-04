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
struct wl_data_offer {int dummy; } ;
struct wl_data_device {int dummy; } ;
struct TYPE_4__ {TYPE_2__* dataOffers; } ;
struct TYPE_6__ {TYPE_1__ wl; } ;
struct TYPE_5__ {scalar_t__ offer_type; struct wl_data_offer* id; } ;

/* Variables and functions */
 scalar_t__ CLIPBOARD ; 
 scalar_t__ EXPIRED ; 
 TYPE_3__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 
 int /*<<< orphan*/  prune_unclaimed_data_offers () ; 

__attribute__((used)) static void mark_selection_offer(void *data, struct wl_data_device *data_device, struct wl_data_offer *data_offer)
{
    for (size_t i = 0; i < arraysz(_glfw.wl.dataOffers); i++) {
        if (_glfw.wl.dataOffers[i].id == data_offer) {
            _glfw.wl.dataOffers[i].offer_type = CLIPBOARD;
        } else if (_glfw.wl.dataOffers[i].offer_type == CLIPBOARD) {
            _glfw.wl.dataOffers[i].offer_type = EXPIRED;  // previous selection offer
        }
    }
    prune_unclaimed_data_offers();
}