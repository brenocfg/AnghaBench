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
struct zwp_primary_selection_offer_v1 {int dummy; } ;
struct zwp_primary_selection_device_v1 {int dummy; } ;
struct TYPE_4__ {TYPE_2__* primarySelectionOffers; } ;
struct TYPE_6__ {TYPE_1__ wl; } ;
struct TYPE_5__ {scalar_t__ offer_type; struct zwp_primary_selection_offer_v1* id; } ;

/* Variables and functions */
 scalar_t__ EXPIRED ; 
 scalar_t__ PRIMARY_SELECTION ; 
 TYPE_3__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 
 int /*<<< orphan*/  prune_unclaimed_primary_selection_offers () ; 

__attribute__((used)) static void mark_primary_selection_offer(void *data, struct zwp_primary_selection_device_v1* primary_selection_device,
        struct zwp_primary_selection_offer_v1 *primary_selection_offer) {
    for (size_t i = 0; i < arraysz(_glfw.wl.primarySelectionOffers); i++) {
        if (_glfw.wl.primarySelectionOffers[i].id == primary_selection_offer) {
            _glfw.wl.primarySelectionOffers[i].offer_type = PRIMARY_SELECTION;
        } else if (_glfw.wl.primarySelectionOffers[i].offer_type == PRIMARY_SELECTION) {
            _glfw.wl.primarySelectionOffers[i].offer_type = EXPIRED;  // previous selection offer
        }
    }
    prune_unclaimed_primary_selection_offers();
}