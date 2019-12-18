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
typedef  int /*<<< orphan*/  targets ;
typedef  int /*<<< orphan*/  formats ;
struct TYPE_6__ {scalar_t__ selection; scalar_t__ property; scalar_t__ target; int /*<<< orphan*/  requestor; } ;
typedef  TYPE_2__ XSelectionRequestEvent ;
struct TYPE_5__ {scalar_t__ const UTF8_STRING; scalar_t__ PRIMARY; char* primarySelectionString; char* clipboardString; scalar_t__ TARGETS; scalar_t__ const MULTIPLE; scalar_t__ ATOM_PAIR; scalar_t__ SAVE_TARGETS; scalar_t__ NULL_; int /*<<< orphan*/  display; } ;
struct TYPE_7__ {TYPE_1__ x11; } ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 scalar_t__ None ; 
 int /*<<< orphan*/  PropModeReplace ; 
 scalar_t__ XA_ATOM ; 
 scalar_t__ const XA_STRING ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  XFree (scalar_t__*) ; 
 TYPE_4__ _glfw ; 
 unsigned long _glfwGetWindowPropertyX11 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned char**) ; 
 unsigned long strlen (char*) ; 

__attribute__((used)) static Atom writeTargetToProperty(const XSelectionRequestEvent* request)
{
    int i;
    char* selectionString = NULL;
    const Atom formats[] = { _glfw.x11.UTF8_STRING, XA_STRING };
    const int formatCount = sizeof(formats) / sizeof(formats[0]);

    if (request->selection == _glfw.x11.PRIMARY)
        selectionString = _glfw.x11.primarySelectionString;
    else
        selectionString = _glfw.x11.clipboardString;

    if (request->property == None)
    {
        // The requester is a legacy client (ICCCM section 2.2)
        // We don't support legacy clients, so fail here
        return None;
    }

    if (request->target == _glfw.x11.TARGETS)
    {
        // The list of supported targets was requested

        const Atom targets[] = { _glfw.x11.TARGETS,
                                 _glfw.x11.MULTIPLE,
                                 _glfw.x11.UTF8_STRING,
                                 XA_STRING };

        XChangeProperty(_glfw.x11.display,
                        request->requestor,
                        request->property,
                        XA_ATOM,
                        32,
                        PropModeReplace,
                        (unsigned char*) targets,
                        sizeof(targets) / sizeof(targets[0]));

        return request->property;
    }

    if (request->target == _glfw.x11.MULTIPLE)
    {
        // Multiple conversions were requested

        Atom* targets;
        unsigned long i, count;

        count = _glfwGetWindowPropertyX11(request->requestor,
                                          request->property,
                                          _glfw.x11.ATOM_PAIR,
                                          (unsigned char**) &targets);

        for (i = 0;  i < count;  i += 2)
        {
            int j;

            for (j = 0;  j < formatCount;  j++)
            {
                if (targets[i] == formats[j])
                    break;
            }

            if (j < formatCount)
            {
                XChangeProperty(_glfw.x11.display,
                                request->requestor,
                                targets[i + 1],
                                targets[i],
                                8,
                                PropModeReplace,
                                (unsigned char *) selectionString,
                                strlen(selectionString));
            }
            else
                targets[i + 1] = None;
        }

        XChangeProperty(_glfw.x11.display,
                        request->requestor,
                        request->property,
                        _glfw.x11.ATOM_PAIR,
                        32,
                        PropModeReplace,
                        (unsigned char*) targets,
                        count);

        XFree(targets);

        return request->property;
    }

    if (request->target == _glfw.x11.SAVE_TARGETS)
    {
        // The request is a check whether we support SAVE_TARGETS
        // It should be handled as a no-op side effect target

        XChangeProperty(_glfw.x11.display,
                        request->requestor,
                        request->property,
                        _glfw.x11.NULL_,
                        32,
                        PropModeReplace,
                        NULL,
                        0);

        return request->property;
    }

    // Conversion to a data target was requested

    for (i = 0;  i < formatCount;  i++)
    {
        if (request->target == formats[i])
        {
            // The requested target is one we support

            XChangeProperty(_glfw.x11.display,
                            request->requestor,
                            request->property,
                            request->target,
                            8,
                            PropModeReplace,
                            (unsigned char *) selectionString,
                            strlen(selectionString));

            return request->property;
        }
    }

    // The requested target is not supported

    return None;
}