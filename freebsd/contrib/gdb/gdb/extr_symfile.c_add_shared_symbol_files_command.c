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

/* Variables and functions */
 int /*<<< orphan*/  ADD_SHARED_SYMBOL_FILES (char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static void
add_shared_symbol_files_command (char *args, int from_tty)
{
#ifdef ADD_SHARED_SYMBOL_FILES
  ADD_SHARED_SYMBOL_FILES (args, from_tty);
#else
  error ("This command is not available in this configuration of GDB.");
#endif
}