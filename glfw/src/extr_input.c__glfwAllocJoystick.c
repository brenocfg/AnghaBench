#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int axisCount; int buttonCount; int hatCount; int /*<<< orphan*/  mapping; int /*<<< orphan*/  guid; void* hats; void* buttons; void* axes; int /*<<< orphan*/  name; int /*<<< orphan*/  present; } ;
typedef  TYPE_1__ _GLFWjoystick ;
struct TYPE_6__ {TYPE_1__* joysticks; } ;

/* Variables and functions */
 int GLFW_JOYSTICK_LAST ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfw_strdup (char const*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  findValidMapping (TYPE_1__*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

_GLFWjoystick* _glfwAllocJoystick(const char* name,
                                  const char* guid,
                                  int axisCount,
                                  int buttonCount,
                                  int hatCount)
{
    int jid;
    _GLFWjoystick* js;

    for (jid = 0;  jid <= GLFW_JOYSTICK_LAST;  jid++)
    {
        if (!_glfw.joysticks[jid].present)
            break;
    }

    if (jid > GLFW_JOYSTICK_LAST)
        return NULL;

    js = _glfw.joysticks + jid;
    js->present     = GLFW_TRUE;
    js->name        = _glfw_strdup(name);
    js->axes        = calloc(axisCount, sizeof(float));
    js->buttons     = calloc(buttonCount + (size_t) hatCount * 4, 1);
    js->hats        = calloc(hatCount, 1);
    js->axisCount   = axisCount;
    js->buttonCount = buttonCount;
    js->hatCount    = hatCount;

    strncpy(js->guid, guid, sizeof(js->guid) - 1);
    js->mapping = findValidMapping(js);

    return js;
}