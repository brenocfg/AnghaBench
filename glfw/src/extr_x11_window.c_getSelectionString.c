#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  targets ;
typedef  int /*<<< orphan*/  XPointer ;
struct TYPE_8__ {scalar_t__ property; int /*<<< orphan*/  requestor; } ;
struct TYPE_9__ {TYPE_2__ xselection; } ;
typedef  TYPE_3__ XEvent ;
struct TYPE_7__ {scalar_t__ const UTF8_STRING; scalar_t__ PRIMARY; char* primarySelectionString; char* clipboardString; scalar_t__ helperWindowHandle; scalar_t__ INCR; int /*<<< orphan*/  display; int /*<<< orphan*/  GLFW_SELECTION; } ;
struct TYPE_10__ {TYPE_1__ x11; } ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  AnyPropertyType ; 
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  GLFW_FORMAT_UNAVAILABLE ; 
 int /*<<< orphan*/  LONG_MAX ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  SelectionNotify ; 
 int /*<<< orphan*/  True ; 
 scalar_t__ const XA_STRING ; 
 int /*<<< orphan*/  XCheckIfEvent (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCheckTypedWindowEvent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  XConvertSelection (int /*<<< orphan*/ ,scalar_t__,scalar_t__ const,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (char*) ; 
 scalar_t__ XGetSelectionOwner (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XGetWindowProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int*,unsigned long*,unsigned long*,unsigned char**) ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 char* _glfw_strdup (char*) ; 
 char* convertLatin1toUTF8 (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isSelPropNewValueNotify ; 
 char* realloc (char*,size_t) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  waitForEvent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char* getSelectionString(Atom selection)
{
    char** selectionString = NULL;
    const Atom targets[] = { _glfw.x11.UTF8_STRING, XA_STRING };
    const size_t targetCount = sizeof(targets) / sizeof(targets[0]);

    if (selection == _glfw.x11.PRIMARY)
        selectionString = &_glfw.x11.primarySelectionString;
    else
        selectionString = &_glfw.x11.clipboardString;

    if (XGetSelectionOwner(_glfw.x11.display, selection) ==
        _glfw.x11.helperWindowHandle)
    {
        // Instead of doing a large number of X round-trips just to put this
        // string into a window property and then read it back, just return it
        return *selectionString;
    }

    free(*selectionString);
    *selectionString = NULL;

    for (size_t i = 0;  i < targetCount;  i++)
    {
        char* data;
        Atom actualType;
        int actualFormat;
        unsigned long itemCount, bytesAfter;
        XEvent notification, dummy;

        XConvertSelection(_glfw.x11.display,
                          selection,
                          targets[i],
                          _glfw.x11.GLFW_SELECTION,
                          _glfw.x11.helperWindowHandle,
                          CurrentTime);

        while (!XCheckTypedWindowEvent(_glfw.x11.display,
                                       _glfw.x11.helperWindowHandle,
                                       SelectionNotify,
                                       &notification))
        {
            waitForEvent(NULL);
        }

        if (notification.xselection.property == None)
            continue;

        XCheckIfEvent(_glfw.x11.display,
                      &dummy,
                      isSelPropNewValueNotify,
                      (XPointer) &notification);

        XGetWindowProperty(_glfw.x11.display,
                           notification.xselection.requestor,
                           notification.xselection.property,
                           0,
                           LONG_MAX,
                           True,
                           AnyPropertyType,
                           &actualType,
                           &actualFormat,
                           &itemCount,
                           &bytesAfter,
                           (unsigned char**) &data);

        if (actualType == _glfw.x11.INCR)
        {
            size_t size = 1;
            char* string = NULL;

            for (;;)
            {
                while (!XCheckIfEvent(_glfw.x11.display,
                                      &dummy,
                                      isSelPropNewValueNotify,
                                      (XPointer) &notification))
                {
                    waitForEvent(NULL);
                }

                XFree(data);
                XGetWindowProperty(_glfw.x11.display,
                                   notification.xselection.requestor,
                                   notification.xselection.property,
                                   0,
                                   LONG_MAX,
                                   True,
                                   AnyPropertyType,
                                   &actualType,
                                   &actualFormat,
                                   &itemCount,
                                   &bytesAfter,
                                   (unsigned char**) &data);

                if (itemCount)
                {
                    size += itemCount;
                    string = realloc(string, size);
                    string[size - itemCount - 1] = '\0';
                    strcat(string, data);
                }

                if (!itemCount)
                {
                    if (targets[i] == XA_STRING)
                    {
                        *selectionString = convertLatin1toUTF8(string);
                        free(string);
                    }
                    else
                        *selectionString = string;

                    break;
                }
            }
        }
        else if (actualType == targets[i])
        {
            if (targets[i] == XA_STRING)
                *selectionString = convertLatin1toUTF8(data);
            else
                *selectionString = _glfw_strdup(data);
        }

        XFree(data);

        if (*selectionString)
            break;
    }

    if (!*selectionString)
    {
        _glfwInputError(GLFW_FORMAT_UNAVAILABLE,
                        "X11: Failed to convert selection to string");
    }

    return *selectionString;
}