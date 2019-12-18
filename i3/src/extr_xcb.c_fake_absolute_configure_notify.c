#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_4__ xcb_rectangle_t ;
struct TYPE_9__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_8__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_12__ {int /*<<< orphan*/  border_width; TYPE_3__* window; TYPE_2__ window_rect; TYPE_1__ rect; } ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_5__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  fake_configure_notify (int /*<<< orphan*/ ,TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fake_absolute_configure_notify(Con *con) {
    xcb_rectangle_t absolute;
    if (con->window == NULL)
        return;

    absolute.x = con->rect.x + con->window_rect.x;
    absolute.y = con->rect.y + con->window_rect.y;
    absolute.width = con->window_rect.width;
    absolute.height = con->window_rect.height;

    DLOG("fake rect = (%d, %d, %d, %d)\n", absolute.x, absolute.y, absolute.width, absolute.height);

    fake_configure_notify(conn, absolute, con->window->id, con->border_width);
}