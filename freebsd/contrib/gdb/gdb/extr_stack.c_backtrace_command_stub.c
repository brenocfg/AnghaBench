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
struct backtrace_command_args {int /*<<< orphan*/  from_tty; int /*<<< orphan*/  show_locals; int /*<<< orphan*/  count_exp; } ;

/* Variables and functions */
 int /*<<< orphan*/  backtrace_command_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
backtrace_command_stub (void *data)
{
  struct backtrace_command_args *args = (struct backtrace_command_args *)data;
  backtrace_command_1 (args->count_exp, args->show_locals, args->from_tty);
  return 0;
}