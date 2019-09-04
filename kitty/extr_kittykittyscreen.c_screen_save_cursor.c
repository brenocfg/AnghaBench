#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  mDECSCNM; int /*<<< orphan*/  mDECAWM; int /*<<< orphan*/  mDECOM; int /*<<< orphan*/  cursor; } ;
struct TYPE_8__ {int /*<<< orphan*/  mDECSCNM; int /*<<< orphan*/  mDECAWM; int /*<<< orphan*/  mDECOM; } ;
struct TYPE_9__ {scalar_t__ linebuf; scalar_t__ main_linebuf; TYPE_1__ modes; int /*<<< orphan*/  cursor; int /*<<< orphan*/  alt_savepoints; int /*<<< orphan*/  main_savepoints; } ;
typedef  TYPE_2__ Screen ;
typedef  int /*<<< orphan*/  SavepointBuffer ;
typedef  TYPE_3__ Savepoint ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_CHARSETS (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  buffer_push (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  cursor_copy_to (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
screen_save_cursor(Screen *self) {
    SavepointBuffer *pts = self->linebuf == self->main_linebuf ? &self->main_savepoints : &self->alt_savepoints;
    Savepoint *sp;
    buffer_push(pts, sp);
    cursor_copy_to(self->cursor, &(sp->cursor));
    sp->mDECOM = self->modes.mDECOM;
    sp->mDECAWM = self->modes.mDECAWM;
    sp->mDECSCNM = self->modes.mDECSCNM;
    COPY_CHARSETS(self, sp);
}