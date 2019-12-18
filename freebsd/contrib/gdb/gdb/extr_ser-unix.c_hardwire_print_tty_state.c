#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ui_file {int dummy; } ;
struct tchars {int dummy; } ;
struct serial {int dummy; } ;
struct ltchars {int dummy; } ;
struct TYPE_6__ {unsigned char sg_flags; } ;
struct TYPE_5__ {unsigned char* c_cc; int /*<<< orphan*/  c_line; int /*<<< orphan*/  c_lflag; int /*<<< orphan*/  c_cflag; int /*<<< orphan*/  c_oflag; int /*<<< orphan*/  c_iflag; } ;
struct TYPE_4__ {unsigned char c_line; unsigned char* c_cc; scalar_t__ c_lflag; scalar_t__ c_cflag; scalar_t__ c_oflag; scalar_t__ c_iflag; } ;
struct hardwire_ttystate {unsigned char lmode; int /*<<< orphan*/  ltc; int /*<<< orphan*/  tc; TYPE_3__ sgttyb; TYPE_2__ termio; TYPE_1__ termios; } ;
typedef  scalar_t__ serial_ttystate ;

/* Variables and functions */
 int NCC ; 
 int NCCS ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 

__attribute__((used)) static void
hardwire_print_tty_state (struct serial *scb,
			  serial_ttystate ttystate,
			  struct ui_file *stream)
{
  struct hardwire_ttystate *state = (struct hardwire_ttystate *) ttystate;
  int i;

#ifdef HAVE_TERMIOS
  fprintf_filtered (stream, "c_iflag = 0x%x, c_oflag = 0x%x,\n",
		    (int) state->termios.c_iflag,
		    (int) state->termios.c_oflag);
  fprintf_filtered (stream, "c_cflag = 0x%x, c_lflag = 0x%x\n",
		    (int) state->termios.c_cflag,
		    (int) state->termios.c_lflag);
#if 0
  /* This not in POSIX, and is not really documented by those systems
     which have it (at least not Sun).  */
  fprintf_filtered (stream, "c_line = 0x%x.\n", state->termios.c_line);
#endif
  fprintf_filtered (stream, "c_cc: ");
  for (i = 0; i < NCCS; i += 1)
    fprintf_filtered (stream, "0x%x ", state->termios.c_cc[i]);
  fprintf_filtered (stream, "\n");
#endif

#ifdef HAVE_TERMIO
  fprintf_filtered (stream, "c_iflag = 0x%x, c_oflag = 0x%x,\n",
		    state->termio.c_iflag, state->termio.c_oflag);
  fprintf_filtered (stream, "c_cflag = 0x%x, c_lflag = 0x%x, c_line = 0x%x.\n",
		    state->termio.c_cflag, state->termio.c_lflag,
		    state->termio.c_line);
  fprintf_filtered (stream, "c_cc: ");
  for (i = 0; i < NCC; i += 1)
    fprintf_filtered (stream, "0x%x ", state->termio.c_cc[i]);
  fprintf_filtered (stream, "\n");
#endif

#ifdef HAVE_SGTTY
  fprintf_filtered (stream, "sgttyb.sg_flags = 0x%x.\n",
		    state->sgttyb.sg_flags);

  fprintf_filtered (stream, "tchars: ");
  for (i = 0; i < (int) sizeof (struct tchars); i++)
    fprintf_filtered (stream, "0x%x ", ((unsigned char *) &state->tc)[i]);
  fprintf_filtered (stream, "\n");

  fprintf_filtered (stream, "ltchars: ");
  for (i = 0; i < (int) sizeof (struct ltchars); i++)
    fprintf_filtered (stream, "0x%x ", ((unsigned char *) &state->ltc)[i]);
  fprintf_filtered (stream, "\n");

  fprintf_filtered (stream, "lmode:  0x%x\n", state->lmode);
#endif
}