#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int fg; int bg; int decoration_fg; } ;
struct TYPE_7__ {int fg; int bg; int decoration_fg; int /*<<< orphan*/  attrs; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ GPUCell ;
typedef  TYPE_2__ Cursor ;

/* Variables and functions */
 int COL_MASK ; 
 int /*<<< orphan*/  CURSOR_TO_ATTRS (TYPE_2__ const*,int) ; 
 char const* cell_as_sgr (TYPE_1__*,TYPE_1__*) ; 

const char*
cursor_as_sgr(const Cursor *self) {
    GPUCell blank_cell = { 0 }, cursor_cell = {
        .attrs = CURSOR_TO_ATTRS(self, 1),
        .fg = self->fg & COL_MASK,
        .bg = self->bg & COL_MASK,
        .decoration_fg = self->decoration_fg & COL_MASK,
    };
    return cell_as_sgr(&cursor_cell, &blank_cell);
}