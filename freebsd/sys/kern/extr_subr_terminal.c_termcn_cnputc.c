#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  teken_attr_t ;
struct terminal {int tm_flags; TYPE_1__* tm_class; int /*<<< orphan*/  tm_emulator; } ;
struct consdev {struct terminal* cn_arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tc_done ) (struct terminal*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TERMINAL_LOCK_CONS (struct terminal*) ; 
 int /*<<< orphan*/  TERMINAL_UNLOCK_CONS (struct terminal*) ; 
 int TF_MUTE ; 
 int /*<<< orphan*/  kernel_message ; 
 int /*<<< orphan*/  stub1 (struct terminal*) ; 
 int /*<<< orphan*/ * teken_get_curattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_input (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  teken_set_curattr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
termcn_cnputc(struct consdev *cp, int c)
{
	struct terminal *tm = cp->cn_arg;
	teken_attr_t backup;
	char cv = c;

	TERMINAL_LOCK_CONS(tm);
	if (!(tm->tm_flags & TF_MUTE)) {
		backup = *teken_get_curattr(&tm->tm_emulator);
		teken_set_curattr(&tm->tm_emulator, &kernel_message);
		teken_input(&tm->tm_emulator, &cv, 1);
		teken_set_curattr(&tm->tm_emulator, &backup);
		tm->tm_class->tc_done(tm);
	}
	TERMINAL_UNLOCK_CONS(tm);
}