#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ width; scalar_t__ height; } ;
struct TYPE_13__ {scalar_t__ deco_height; scalar_t__ y; scalar_t__* sizes; TYPE_1__ rect; scalar_t__ x; } ;
typedef  TYPE_4__ render_params ;
struct TYPE_12__ {scalar_t__ height; scalar_t__ width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_11__ {scalar_t__ width; scalar_t__ height; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_14__ {scalar_t__ layout; scalar_t__ border_style; TYPE_3__ deco_rect; TYPE_2__ rect; } ;
typedef  TYPE_5__ Con ;

/* Variables and functions */
 scalar_t__ BS_NORMAL ; 
 scalar_t__ L_SPLITH ; 
 scalar_t__ L_SPLITV ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ con_is_leaf (TYPE_5__*) ; 

__attribute__((used)) static void render_con_split(Con *con, Con *child, render_params *p, int i) {
    assert(con->layout == L_SPLITH || con->layout == L_SPLITV);

    if (con->layout == L_SPLITH) {
        child->rect.x = p->x;
        child->rect.y = p->y;
        child->rect.width = p->sizes[i];
        child->rect.height = p->rect.height;
        p->x += child->rect.width;
    } else {
        child->rect.x = p->x;
        child->rect.y = p->y;
        child->rect.width = p->rect.width;
        child->rect.height = p->sizes[i];
        p->y += child->rect.height;
    }

    /* first we have the decoration, if this is a leaf node */
    if (con_is_leaf(child)) {
        if (child->border_style == BS_NORMAL) {
            /* TODO: make a function for relative coords? */
            child->deco_rect.x = child->rect.x - con->rect.x;
            child->deco_rect.y = child->rect.y - con->rect.y;

            child->rect.y += p->deco_height;
            child->rect.height -= p->deco_height;

            child->deco_rect.width = child->rect.width;
            child->deco_rect.height = p->deco_height;
        } else {
            child->deco_rect.x = 0;
            child->deco_rect.y = 0;
            child->deco_rect.width = 0;
            child->deco_rect.height = 0;
        }
    }
}