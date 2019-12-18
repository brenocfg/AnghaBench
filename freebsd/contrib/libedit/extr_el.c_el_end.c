#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_4__* wbuff; TYPE_4__* cbuff; } ;
struct TYPE_19__ {TYPE_4__* wbuff; TYPE_4__* cbuff; } ;
struct TYPE_18__ {TYPE_4__* wbuff; TYPE_4__* cbuff; } ;
struct TYPE_21__ {int el_flags; TYPE_3__ el_lgcyconv; TYPE_2__ el_scratch; TYPE_1__ el_visual; struct TYPE_21__* el_prog; int /*<<< orphan*/  el_read; } ;
typedef  TYPE_4__ EditLine ;

/* Variables and functions */
 int NO_TTY ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  ch_end (TYPE_4__*) ; 
 int /*<<< orphan*/  el_free (TYPE_4__*) ; 
 int /*<<< orphan*/  el_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  hist_end (TYPE_4__*) ; 
 int /*<<< orphan*/  keymacro_end (TYPE_4__*) ; 
 int /*<<< orphan*/  literal_end (TYPE_4__*) ; 
 int /*<<< orphan*/  map_end (TYPE_4__*) ; 
 int /*<<< orphan*/  prompt_end (TYPE_4__*) ; 
 int /*<<< orphan*/  read_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  search_end (TYPE_4__*) ; 
 int /*<<< orphan*/  sig_end (TYPE_4__*) ; 
 int /*<<< orphan*/  terminal_end (TYPE_4__*) ; 
 int /*<<< orphan*/  tty_end (TYPE_4__*,int /*<<< orphan*/ ) ; 

void
el_end(EditLine *el)
{

	if (el == NULL)
		return;

	el_reset(el);

	terminal_end(el);
	keymacro_end(el);
	map_end(el);
	if (!(el->el_flags & NO_TTY))
		tty_end(el, TCSAFLUSH);
	ch_end(el);
	read_end(el->el_read);
	search_end(el);
	hist_end(el);
	prompt_end(el);
	sig_end(el);
	literal_end(el);

	el_free(el->el_prog);
	el_free(el->el_visual.cbuff);
	el_free(el->el_visual.wbuff);
	el_free(el->el_scratch.cbuff);
	el_free(el->el_scratch.wbuff);
	el_free(el->el_lgcyconv.cbuff);
	el_free(el->el_lgcyconv.wbuff);
	el_free(el);
}