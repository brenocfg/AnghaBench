#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  event_mask; } ;
typedef  TYPE_2__ XSetWindowAttributes ;
typedef  int /*<<< orphan*/  Window ;
struct TYPE_5__ {int /*<<< orphan*/  screen; int /*<<< orphan*/  display; int /*<<< orphan*/  root; } ;
struct TYPE_7__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  CWEventMask ; 
 int /*<<< orphan*/  DefaultVisual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InputOnly ; 
 int /*<<< orphan*/  PropertyChangeMask ; 
 int /*<<< orphan*/  XCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_3__ _glfw ; 

__attribute__((used)) static Window createHelperWindow(void)
{
    XSetWindowAttributes wa;
    wa.event_mask = PropertyChangeMask;

    return XCreateWindow(_glfw.x11.display, _glfw.x11.root,
                         0, 0, 1, 1, 0, 0,
                         InputOnly,
                         DefaultVisual(_glfw.x11.display, _glfw.x11.screen),
                         CWEventMask, &wa);
}