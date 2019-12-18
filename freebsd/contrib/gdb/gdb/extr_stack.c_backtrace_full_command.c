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
struct backtrace_command_args {char* count_exp; int show_locals; int from_tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ERROR ; 
 int /*<<< orphan*/  backtrace_command_stub ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
backtrace_full_command (char *arg, int from_tty)
{
  struct backtrace_command_args btargs;
  btargs.count_exp = arg;
  btargs.show_locals = 1;
  btargs.from_tty = from_tty;
  catch_errors (backtrace_command_stub, (char *)&btargs, "", RETURN_MASK_ERROR);
}