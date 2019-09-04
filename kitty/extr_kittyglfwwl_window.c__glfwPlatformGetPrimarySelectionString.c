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
struct TYPE_4__ {char const* primarySelectionString; char const* pasteString; TYPE_2__* primarySelectionOffers; int /*<<< orphan*/ * dataSourceForPrimarySelection; } ;
struct TYPE_6__ {TYPE_1__ wl; } ;
struct TYPE_5__ {scalar_t__ offer_type; scalar_t__ mime; scalar_t__ id; scalar_t__ is_self_offer; } ;

/* Variables and functions */
 scalar_t__ PRIMARY_SELECTION ; 
 TYPE_3__ _glfw ; 
 size_t arraysz (TYPE_2__*) ; 
 int /*<<< orphan*/  free (char const*) ; 
 char const* read_primary_selection_offer (scalar_t__,scalar_t__) ; 

const char* _glfwPlatformGetPrimarySelectionString(void)
{
    if (_glfw.wl.dataSourceForPrimarySelection != NULL) return _glfw.wl.primarySelectionString;

    for (size_t i = 0; i < arraysz(_glfw.wl.primarySelectionOffers); i++) {
        if (_glfw.wl.primarySelectionOffers[i].id && _glfw.wl.primarySelectionOffers[i].mime && _glfw.wl.primarySelectionOffers[i].offer_type == PRIMARY_SELECTION) {
            if (_glfw.wl.primarySelectionOffers[i].is_self_offer) {
                return _glfw.wl.primarySelectionString;
            }
            free(_glfw.wl.pasteString);
            _glfw.wl.pasteString = read_primary_selection_offer(_glfw.wl.primarySelectionOffers[i].id, _glfw.wl.primarySelectionOffers[i].mime);
            return _glfw.wl.pasteString;
        }
    }
    return NULL;
}