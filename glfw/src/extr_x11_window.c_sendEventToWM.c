#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  handle; } ;
struct TYPE_14__ {TYPE_1__ x11; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_11__ {long* l; } ;
struct TYPE_12__ {int format; TYPE_2__ data; int /*<<< orphan*/  message_type; int /*<<< orphan*/  window; } ;
struct TYPE_15__ {TYPE_3__ xclient; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ XEvent ;
struct TYPE_13__ {int /*<<< orphan*/  root; int /*<<< orphan*/  display; } ;
struct TYPE_16__ {TYPE_4__ x11; } ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  ClientMessage ; 
 int /*<<< orphan*/  False ; 
 int SubstructureNotifyMask ; 
 int SubstructureRedirectMask ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_6__*) ; 
 TYPE_8__ _glfw ; 

__attribute__((used)) static void sendEventToWM(_GLFWwindow* window, Atom type,
                          long a, long b, long c, long d, long e)
{
    XEvent event = { ClientMessage };
    event.xclient.window = window->x11.handle;
    event.xclient.format = 32; // Data is 32-bit longs
    event.xclient.message_type = type;
    event.xclient.data.l[0] = a;
    event.xclient.data.l[1] = b;
    event.xclient.data.l[2] = c;
    event.xclient.data.l[3] = d;
    event.xclient.data.l[4] = e;

    XSendEvent(_glfw.x11.display, _glfw.x11.root,
               False,
               SubstructureNotifyMask | SubstructureRedirectMask,
               &event);
}