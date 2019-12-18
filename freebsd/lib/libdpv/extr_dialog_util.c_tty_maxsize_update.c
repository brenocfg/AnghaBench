#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct winsize {int dummy; } ;
struct termios {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ws_col; int /*<<< orphan*/  ws_row; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int STDIN_FILENO ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int /*<<< orphan*/  TTY_DEFAULT_COLS ; 
 int /*<<< orphan*/  TTY_DEFAULT_ROWS ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  isatty (int) ; 
 TYPE_1__* malloc (int) ; 
 TYPE_1__* maxsize ; 
 int /*<<< orphan*/  memset (void*,char,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcgetattr (int,struct termios*) ; 

__attribute__((used)) static void
tty_maxsize_update(void)
{
	int fd = STDIN_FILENO;
	struct termios t;

	if (maxsize == NULL) {
		if ((maxsize = malloc(sizeof(struct winsize))) == NULL)
			errx(EXIT_FAILURE, "Out of memory?!");
		memset((void *)maxsize, '\0', sizeof(struct winsize));
	}

	if (!isatty(fd))
		fd = open("/dev/tty", O_RDONLY);
	if ((tcgetattr(fd, &t) < 0) || (ioctl(fd, TIOCGWINSZ, maxsize) < 0)) {
		maxsize->ws_row = TTY_DEFAULT_ROWS;
		maxsize->ws_col = TTY_DEFAULT_COLS;
	}
}