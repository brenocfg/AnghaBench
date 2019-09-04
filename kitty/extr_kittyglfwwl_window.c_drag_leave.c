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
struct wl_data_device {int dummy; } ;
struct TYPE_5__ {TYPE_2__* dataOffers; } ;
struct TYPE_7__ {TYPE_1__ wl; } ;
struct TYPE_6__ {scalar_t__ offer_type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ DRAG_AND_DROP ; 
 TYPE_4__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wl_data_offer_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drag_leave(void *data, struct wl_data_device *wl_data_device) {
    for (size_t i = 0; i < arraysz(_glfw.wl.dataOffers); i++) {
        if (_glfw.wl.dataOffers[i].offer_type == DRAG_AND_DROP) {
            wl_data_offer_destroy(_glfw.wl.dataOffers[i].id);
            memset(_glfw.wl.dataOffers + i, 0, sizeof(_glfw.wl.dataOffers[0]));
        }
    }
}