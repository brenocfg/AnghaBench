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
struct _GLFWWaylandDataOffer {int dummy; } ;
struct TYPE_4__ {TYPE_2__* primarySelectionOffers; } ;
struct TYPE_6__ {TYPE_1__ wl; } ;
struct TYPE_5__ {struct zwp_primary_selection_offer_v1* id; } ;

/* Variables and functions */
 TYPE_3__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 
 int /*<<< orphan*/  set_offer_mimetype (struct _GLFWWaylandDataOffer*,char const*) ; 

__attribute__((used)) static void handle_primary_selection_offer_mimetype(void *data, struct zwp_primary_selection_offer_v1* id, const char *mime) {
    for (size_t i = 0; i < arraysz(_glfw.wl.primarySelectionOffers); i++) {
        if (_glfw.wl.primarySelectionOffers[i].id == id) {
            set_offer_mimetype((struct _GLFWWaylandDataOffer*)&_glfw.wl.primarySelectionOffers[i], mime);
            break;
        }
    }
}