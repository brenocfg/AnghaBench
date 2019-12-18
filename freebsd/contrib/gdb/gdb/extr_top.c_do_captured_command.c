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
struct captured_command_args {int /*<<< orphan*/  from_tty; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* command ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CLEANUPS ; 
 int /*<<< orphan*/  do_cleanups (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_captured_command (void *data)
{
  struct captured_command_args *context = data;
  context->command (context->arg, context->from_tty);
  /* FIXME: cagney/1999-11-07: Technically this do_cleanups() call
     isn't needed.  Instead an assertion check could be made that
     simply confirmed that the called function correctly cleaned up
     after itself.  Unfortunately, old code (prior to 1999-11-04) in
     main.c was calling SET_TOP_LEVEL(), calling the command function,
     and then *always* calling do_cleanups().  For the moment we
     remain ``bug compatible'' with that old code..  */
  do_cleanups (ALL_CLEANUPS);
  return 1;
}