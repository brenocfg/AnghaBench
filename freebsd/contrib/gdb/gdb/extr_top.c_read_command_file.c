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
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  command_loop () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_restore_instream_cleanup ; 
 int /*<<< orphan*/ * instream ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
read_command_file (FILE *stream)
{
  struct cleanup *cleanups;

  cleanups = make_cleanup (do_restore_instream_cleanup, instream);
  instream = stream;
  command_loop ();
  do_cleanups (cleanups);
}