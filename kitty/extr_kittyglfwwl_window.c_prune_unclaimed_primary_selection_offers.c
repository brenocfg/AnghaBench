#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* primarySelectionOffers; TYPE_1__* dataOffers; } ;
struct TYPE_9__ {TYPE_2__ wl; } ;
struct TYPE_8__ {scalar_t__ id; } ;
struct TYPE_6__ {int /*<<< orphan*/  offer_type; } ;

/* Variables and functions */
 TYPE_5__ _glfw ; 
 size_t arraysz (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zwp_primary_selection_offer_v1_destroy (scalar_t__) ; 

__attribute__((used)) static void prune_unclaimed_primary_selection_offers() {
    for (size_t i = 0; i < arraysz(_glfw.wl.primarySelectionOffers); i++) {
        if (_glfw.wl.primarySelectionOffers[i].id && !_glfw.wl.dataOffers[i].offer_type) {
            zwp_primary_selection_offer_v1_destroy(_glfw.wl.primarySelectionOffers[i].id);
            memset(_glfw.wl.primarySelectionOffers + i, 0, sizeof(_glfw.wl.primarySelectionOffers[0]));
        }
    }
}