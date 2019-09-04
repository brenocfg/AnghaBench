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
struct TYPE_5__ {TYPE_2__* dataOffers; } ;
struct TYPE_7__ {TYPE_1__ wl; } ;
struct TYPE_6__ {struct wl_data_offer* id; } ;

/* Variables and functions */
 TYPE_4__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 
 int /*<<< orphan*/  set_offer_mimetype (TYPE_2__*,char const*) ; 

__attribute__((used)) static void handle_offer_mimetype(void *data, struct wl_data_offer* id, const char *mime) {
    for (size_t i = 0; i < arraysz(_glfw.wl.dataOffers); i++) {
        if (_glfw.wl.dataOffers[i].id == id) {
            set_offer_mimetype(&_glfw.wl.dataOffers[i], mime);
            break;
        }
    }
}