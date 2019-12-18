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
struct TYPE_10__ {int /*<<< orphan*/  tp_col; int /*<<< orphan*/  tp_row; } ;
struct TYPE_7__ {scalar_t__ tp_col; scalar_t__ tp_row; } ;
struct TYPE_9__ {TYPE_4__ tr_end; TYPE_1__ tr_begin; } ;
typedef  TYPE_3__ term_rect_t ;
typedef  int /*<<< orphan*/  term_attr_t ;
typedef  int /*<<< orphan*/  teken_char_t ;
struct winsize {int /*<<< orphan*/  ws_col; int /*<<< orphan*/  ws_row; } ;
struct terminal {int tm_flags; TYPE_2__* tm_class; int /*<<< orphan*/  tm_emulator; struct winsize tm_winsize; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* tc_fill ) (struct terminal*,TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TCHAR_CREATE (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TERMINAL_LOCK (struct terminal*) ; 
 int /*<<< orphan*/  TERMINAL_UNLOCK (struct terminal*) ; 
 int TF_MUTE ; 
 int /*<<< orphan*/  stub1 (struct terminal*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teken_set_winsize (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  teken_set_winsize_noreset (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  terminal_sync_ttysize (struct terminal*) ; 

void
terminal_set_winsize_blank(struct terminal *tm, const struct winsize *size,
    int blank, const term_attr_t *attr)
{
	term_rect_t r;

	tm->tm_winsize = *size;

	r.tr_begin.tp_row = r.tr_begin.tp_col = 0;
	r.tr_end.tp_row = size->ws_row;
	r.tr_end.tp_col = size->ws_col;

	TERMINAL_LOCK(tm);
	if (blank == 0)
		teken_set_winsize_noreset(&tm->tm_emulator, &r.tr_end);
	else
		teken_set_winsize(&tm->tm_emulator, &r.tr_end);
	TERMINAL_UNLOCK(tm);

	if ((blank != 0) && !(tm->tm_flags & TF_MUTE))
		tm->tm_class->tc_fill(tm, &r,
		    TCHAR_CREATE((teken_char_t)' ', attr));

	terminal_sync_ttysize(tm);
}