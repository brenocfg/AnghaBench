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
struct column_options {int width; int indent; int padding; } ;
struct argv_array {int dummy; } ;
struct TYPE_4__ {int in; int git_cmd; void* out; struct argv_array args; } ;

/* Variables and functions */
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int) ; 
 int /*<<< orphan*/  child_process_init (TYPE_1__*) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ column_process ; 
 void* dup (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int fd_out ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (TYPE_1__*) ; 
 int /*<<< orphan*/  stdout ; 

int run_column_filter(int colopts, const struct column_options *opts)
{
	struct argv_array *argv;

	if (fd_out != -1)
		return -1;

	child_process_init(&column_process);
	argv = &column_process.args;

	argv_array_push(argv, "column");
	argv_array_pushf(argv, "--raw-mode=%d", colopts);
	if (opts && opts->width)
		argv_array_pushf(argv, "--width=%d", opts->width);
	if (opts && opts->indent)
		argv_array_pushf(argv, "--indent=%s", opts->indent);
	if (opts && opts->padding)
		argv_array_pushf(argv, "--padding=%d", opts->padding);

	fflush(stdout);
	column_process.in = -1;
	column_process.out = dup(1);
	column_process.git_cmd = 1;

	if (start_command(&column_process))
		return -2;

	fd_out = dup(1);
	close(1);
	dup2(column_process.in, 1);
	close(column_process.in);
	return 0;
}