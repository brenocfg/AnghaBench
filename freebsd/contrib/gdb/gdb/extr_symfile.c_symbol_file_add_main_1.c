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
 int /*<<< orphan*/  RESET_HP_UX_GLOBALS () ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 int /*<<< orphan*/  set_initial_language () ; 
 int /*<<< orphan*/  symbol_file_add (char*,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
symbol_file_add_main_1 (char *args, int from_tty, int flags)
{
  symbol_file_add (args, from_tty, NULL, 1, flags);

#ifdef HPUXHPPA
  RESET_HP_UX_GLOBALS ();
#endif

  /* Getting new symbols may change our opinion about
     what is frameless.  */
  reinit_frame_cache ();

  set_initial_language ();
}