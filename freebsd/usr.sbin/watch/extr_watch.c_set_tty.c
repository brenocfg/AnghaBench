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
struct termios {int* c_cc; int /*<<< orphan*/  c_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHO ; 
 int /*<<< orphan*/  FLUSHO ; 
 int /*<<< orphan*/  ICANON ; 
 int /*<<< orphan*/  IEXTEN ; 
 int /*<<< orphan*/  PENDIN ; 
 int /*<<< orphan*/  TCSANOW ; 
 size_t VINTR ; 
 size_t VMIN ; 
 size_t VQUIT ; 
 size_t VTIME ; 
 struct termios otty ; 
 int /*<<< orphan*/  std_in ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void
set_tty(void)
{
	struct termios	ntty;

	ntty = otty;
	ntty.c_lflag &= ~ICANON;	/* disable canonical operation */
	ntty.c_lflag &= ~ECHO;
#ifdef FLUSHO
	ntty.c_lflag &= ~FLUSHO;
#endif
#ifdef PENDIN
	ntty.c_lflag &= ~PENDIN;
#endif
#ifdef IEXTEN
	ntty.c_lflag &= ~IEXTEN;
#endif
	ntty.c_cc[VMIN] = 1;		/* minimum of one character */
	ntty.c_cc[VTIME] = 0;		/* timeout value */

	ntty.c_cc[VINTR] = 07;		/* ^G */
	ntty.c_cc[VQUIT] = 07;		/* ^G */
	tcsetattr(std_in, TCSANOW, &ntty);
}