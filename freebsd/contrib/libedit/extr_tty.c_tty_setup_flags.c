#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tcflag_t ;
struct termios {int dummy; } ;
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 int MD_INP ; 
 int MD_LIN ; 
 int /*<<< orphan*/ * tty__get_flag (struct termios*,int) ; 
 int /*<<< orphan*/  tty_update_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
tty_setup_flags(EditLine *el, struct termios *tios, int mode)
{
	int kind;
	for (kind = MD_INP; kind <= MD_LIN; kind++) {
		tcflag_t *f = tty__get_flag(tios, kind);
		*f = tty_update_flag(el, *f, mode, kind);
	}
}