#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int height; int /*<<< orphan*/  width; } ;
struct TYPE_12__ {int y; int deco_height; int children; scalar_t__ x; TYPE_1__ rect; } ;
typedef  TYPE_4__ render_params ;
struct TYPE_11__ {int y; int height; int /*<<< orphan*/  width; scalar_t__ x; } ;
struct TYPE_10__ {int y; int height; int /*<<< orphan*/  width; scalar_t__ x; } ;
struct TYPE_13__ {scalar_t__ layout; scalar_t__ border_style; TYPE_3__ rect; TYPE_2__ deco_rect; } ;
typedef  TYPE_5__ Con ;

/* Variables and functions */
 scalar_t__ BS_NONE ; 
 scalar_t__ BS_PIXEL ; 
 scalar_t__ L_STACKED ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void render_con_stacked(Con *con, Con *child, render_params *p, int i) {
    assert(con->layout == L_STACKED);

    child->rect.x = p->x;
    child->rect.y = p->y;
    child->rect.width = p->rect.width;
    child->rect.height = p->rect.height;

    child->deco_rect.x = p->x - con->rect.x;
    child->deco_rect.y = p->y - con->rect.y + (i * p->deco_height);
    child->deco_rect.width = child->rect.width;
    child->deco_rect.height = p->deco_height;

    if (p->children > 1 || (child->border_style != BS_PIXEL && child->border_style != BS_NONE)) {
        child->rect.y += (p->deco_height * p->children);
        child->rect.height -= (p->deco_height * p->children);
    }
}