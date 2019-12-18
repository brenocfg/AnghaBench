#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int count_styles; int* supported_styles; } ;
typedef  TYPE_2__ XIMStyles ;
struct TYPE_6__ {int /*<<< orphan*/  im; } ;
struct TYPE_8__ {TYPE_1__ x11; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  XFree (TYPE_2__*) ; 
 int /*<<< orphan*/ * XGetIMValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int XIMPreeditNothing ; 
 int XIMStatusNothing ; 
 int /*<<< orphan*/  XNQueryInputStyle ; 
 TYPE_3__ _glfw ; 

__attribute__((used)) static GLFWbool hasUsableInputMethodStyle(void)
{
    GLFWbool found = GLFW_FALSE;
    XIMStyles* styles = NULL;

    if (XGetIMValues(_glfw.x11.im, XNQueryInputStyle, &styles, NULL) != NULL)
        return GLFW_FALSE;

    for (unsigned int i = 0;  i < styles->count_styles;  i++)
    {
        if (styles->supported_styles[i] == (XIMPreeditNothing | XIMStatusNothing))
        {
            found = GLFW_TRUE;
            break;
        }
    }

    XFree(styles);
    return found;
}