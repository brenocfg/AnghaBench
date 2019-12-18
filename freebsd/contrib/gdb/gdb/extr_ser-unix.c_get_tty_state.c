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
struct serial {int /*<<< orphan*/  fd; } ;
struct hardwire_ttystate {int /*<<< orphan*/  lmode; int /*<<< orphan*/  ltc; int /*<<< orphan*/  tc; int /*<<< orphan*/  sgttyb; int /*<<< orphan*/  termio; int /*<<< orphan*/  termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCGETA ; 
 int /*<<< orphan*/  TIOCGETC ; 
 int /*<<< orphan*/  TIOCGETP ; 
 int /*<<< orphan*/  TIOCGLTC ; 
 int /*<<< orphan*/  TIOCLGET ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_tty_state (struct serial *scb, struct hardwire_ttystate *state)
{
#ifdef HAVE_TERMIOS
  if (tcgetattr (scb->fd, &state->termios) < 0)
    return -1;

  return 0;
#endif

#ifdef HAVE_TERMIO
  if (ioctl (scb->fd, TCGETA, &state->termio) < 0)
    return -1;
  return 0;
#endif

#ifdef HAVE_SGTTY
  if (ioctl (scb->fd, TIOCGETP, &state->sgttyb) < 0)
    return -1;
  if (ioctl (scb->fd, TIOCGETC, &state->tc) < 0)
    return -1;
  if (ioctl (scb->fd, TIOCGLTC, &state->ltc) < 0)
    return -1;
  if (ioctl (scb->fd, TIOCLGET, &state->lmode) < 0)
    return -1;

  return 0;
#endif
}