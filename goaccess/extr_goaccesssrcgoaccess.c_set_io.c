#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ output_format_idx; int output_stdout; int /*<<< orphan*/  load_from_disk; int /*<<< orphan*/  read_stdin; int /*<<< orphan*/  filenames_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  cmd_help () ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pipe_stdin () ; 

__attribute__((used)) static void
set_io (void)
{
  /* For backwards compatibility, check if we are not outputting to a
   * terminal or if an output format was supplied */
  if (!isatty (STDOUT_FILENO) || conf.output_format_idx > 0)
    conf.output_stdout = 1;
  /* dup fd if data piped */
  if (!isatty (STDIN_FILENO))
    set_pipe_stdin ();
  /* No data piped, no file was used and not loading from disk */
  if (!conf.filenames_idx && !conf.read_stdin && !conf.load_from_disk)
    cmd_help ();
}