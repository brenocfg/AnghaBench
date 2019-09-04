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
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_data_offer {int dummy; } ;
struct TYPE_4__ {TYPE_2__* dataOffers; } ;
struct TYPE_6__ {TYPE_1__ wl; } ;
struct TYPE_5__ {int /*<<< orphan*/  dnd_action; struct wl_data_offer* id; } ;

/* Variables and functions */
 TYPE_3__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 

__attribute__((used)) static void data_offer_action(void *data, struct wl_data_offer* id, uint32_t action) {
    for (size_t i = 0; i < arraysz(_glfw.wl.dataOffers); i++) {
        if (_glfw.wl.dataOffers[i].id == id) {
            _glfw.wl.dataOffers[i].dnd_action = action;
            break;
        }
    }
}