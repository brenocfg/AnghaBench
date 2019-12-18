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
typedef  int /*<<< orphan*/  gdb_client_data ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ tui_active ; 
 int /*<<< orphan*/  tui_puts (char*) ; 
 int /*<<< orphan*/ * tui_readline_pipe ; 

__attribute__((used)) static void
tui_readline_output (int code, gdb_client_data data)
{
  int size;
  char buf[256];

  size = read (tui_readline_pipe[0], buf, sizeof (buf) - 1);
  if (size > 0 && tui_active)
    {
      buf[size] = 0;
      tui_puts (buf);
    }
}