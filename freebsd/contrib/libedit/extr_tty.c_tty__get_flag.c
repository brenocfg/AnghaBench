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
struct termios {int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_cflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; } ;

/* Variables and functions */
#define  MD_CTL 131 
#define  MD_INP 130 
#define  MD_LIN 129 
#define  MD_OUT 128 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static tcflag_t *
tty__get_flag(struct termios *t, int kind) {
	switch (kind) {
	case MD_INP:
		return &t->c_iflag;
	case MD_OUT:
		return &t->c_oflag;
	case MD_CTL:
		return &t->c_cflag;
	case MD_LIN:
		return &t->c_lflag;
	default:
		abort();
		/*NOTREACHED*/
	}
}