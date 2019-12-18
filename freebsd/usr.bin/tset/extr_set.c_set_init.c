#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int c_oflag; } ;

/* Variables and functions */
 int OCRNL ; 
 int ONLCR ; 
 int ONLRET ; 
 char PC ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int TAB3 ; 
 int /*<<< orphan*/  TCSADRAIN ; 
 int /*<<< orphan*/  cat (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ isreset ; 
 TYPE_1__ oldmode ; 
 int /*<<< orphan*/  outc ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int set_tabs () ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ tgetstr (char*,char**) ; 
 int /*<<< orphan*/  tputs (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
set_init(void)
{
	char *bp, buf[1024];
	int settle;

	bp = buf;
	if (tgetstr("pc", &bp) != 0)		/* Get/set pad character. */
		PC = buf[0];

#ifdef TAB3
	if (oldmode.c_oflag & (TAB3 | ONLCR | OCRNL | ONLRET)) {
		oldmode.c_oflag &= (TAB3 | ONLCR | OCRNL | ONLRET);
		tcsetattr(STDERR_FILENO, TCSADRAIN, &oldmode);
	}
#endif
	settle = set_tabs();

	if (isreset) {
		bp = buf;
		if (tgetstr("rs", &bp) != 0 || tgetstr("is", &bp) != 0) {
			tputs(buf, 0, outc);
			settle = 1;
		}
		bp = buf;
		if (tgetstr("rf", &bp) != 0 || tgetstr("if", &bp) != 0) {
			cat(buf);
			settle = 1;
		}
	}

	if (settle) {
		(void)putc('\r', stderr);
		(void)fflush(stderr);
		(void)sleep(1);			/* Settle the terminal. */
	}
}