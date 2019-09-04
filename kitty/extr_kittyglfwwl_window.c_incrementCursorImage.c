#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ focus; } ;
struct TYPE_11__ {TYPE_6__* currentCursor; TYPE_1__ decorations; } ;
struct TYPE_14__ {TYPE_2__ wl; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_16__ {int currentImage; TYPE_3__* cursor; } ;
struct TYPE_15__ {TYPE_7__ wl; } ;
typedef  TYPE_6__ _GLFWcursor ;
struct TYPE_13__ {int /*<<< orphan*/  cursorAnimationTimer; int /*<<< orphan*/  eventLoopData; } ;
struct TYPE_17__ {TYPE_4__ wl; } ;
struct TYPE_12__ {int image_count; } ;

/* Variables and functions */
 TYPE_9__ _glfw ; 
 scalar_t__ mainWindow ; 
 int /*<<< orphan*/  setCursorImage (TYPE_7__*) ; 
 int /*<<< orphan*/  toggleTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
incrementCursorImage(_GLFWwindow* window)
{
    if (window && window->wl.decorations.focus == mainWindow) {
        _GLFWcursor* cursor = window->wl.currentCursor;
        if (cursor && cursor->wl.cursor)
        {
            cursor->wl.currentImage += 1;
            cursor->wl.currentImage %= cursor->wl.cursor->image_count;
            setCursorImage(&cursor->wl);
            toggleTimer(&_glfw.wl.eventLoopData, _glfw.wl.cursorAnimationTimer, cursor->wl.cursor->image_count > 1);
            return;
        }
    }
    toggleTimer(&_glfw.wl.eventLoopData, _glfw.wl.cursorAnimationTimer, 1);
}