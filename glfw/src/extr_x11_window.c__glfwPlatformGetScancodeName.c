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
struct TYPE_4__ {int /*<<< orphan*/  group; int /*<<< orphan*/  available; } ;
struct TYPE_5__ {int* keycodes; char** keynames; TYPE_1__ xkb; int /*<<< orphan*/  display; } ;
struct TYPE_6__ {TYPE_2__ x11; } ;
typedef  scalar_t__ KeySym ;

/* Variables and functions */
 scalar_t__ const NoSymbol ; 
 scalar_t__ XkbKeycodeToKeysym (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ _glfw ; 
 long _glfwKeySym2Unicode (scalar_t__ const) ; 
 size_t encodeUTF8 (char*,unsigned int) ; 

const char* _glfwPlatformGetScancodeName(int scancode)
{
    if (!_glfw.x11.xkb.available)
        return NULL;

    const int key = _glfw.x11.keycodes[scancode];
    const KeySym keysym = XkbKeycodeToKeysym(_glfw.x11.display,
                                             scancode, _glfw.x11.xkb.group, 0);
    if (keysym == NoSymbol)
        return NULL;

    const long ch = _glfwKeySym2Unicode(keysym);
    if (ch == -1)
        return NULL;

    const size_t count = encodeUTF8(_glfw.x11.keynames[key], (unsigned int) ch);
    if (count == 0)
        return NULL;

    _glfw.x11.keynames[key][count] = '\0';
    return _glfw.x11.keynames[key];
}