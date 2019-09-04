#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cursor; int /*<<< orphan*/  mDECSCNM; int /*<<< orphan*/  mDECAWM; int /*<<< orphan*/  mDECOM; } ;
struct TYPE_11__ {scalar_t__ linebuf; scalar_t__ main_linebuf; int /*<<< orphan*/  cursor; int /*<<< orphan*/  g0_charset; int /*<<< orphan*/  g1_charset; scalar_t__ current_charset; int /*<<< orphan*/  g_charset; int /*<<< orphan*/  alt_savepoints; int /*<<< orphan*/  main_savepoints; } ;
typedef  TYPE_1__ Screen ;
typedef  int /*<<< orphan*/  SavepointBuffer ;
typedef  TYPE_2__ Savepoint ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_CHARSETS (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DECAWM ; 
 int /*<<< orphan*/  DECOM ; 
 int /*<<< orphan*/  DECSCNM ; 
 int /*<<< orphan*/  RESET_CHARSETS ; 
 int /*<<< orphan*/  buffer_pop (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  cursor_copy_to (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_cursor_position (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  screen_ensure_bounds (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  screen_reset_mode (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mode_from_const (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
screen_restore_cursor(Screen *self) {
    SavepointBuffer *pts = self->linebuf == self->main_linebuf ? &self->main_savepoints : &self->alt_savepoints;
    Savepoint *sp;
    buffer_pop(pts, sp);
    if (sp == NULL) {
        screen_cursor_position(self, 1, 1);
        screen_reset_mode(self, DECOM);
        RESET_CHARSETS;
        screen_reset_mode(self, DECSCNM);
    } else {
        COPY_CHARSETS(sp, self);
        self->g_charset = self->current_charset ? self->g1_charset : self->g0_charset;
        set_mode_from_const(self, DECOM, sp->mDECOM);
        set_mode_from_const(self, DECAWM, sp->mDECAWM);
        set_mode_from_const(self, DECSCNM, sp->mDECSCNM);
        cursor_copy_to(&(sp->cursor), self->cursor);
        screen_ensure_bounds(self, false, false);
    }
}