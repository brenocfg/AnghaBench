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
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_exit ; 
 int /*<<< orphan*/  tui_initialize_io () ; 
 int /*<<< orphan*/  tui_initialize_readline () ; 
 int /*<<< orphan*/  tui_initialize_static_data () ; 

__attribute__((used)) static void *
tui_init (void)
{
  /* Install exit handler to leave the screen in a good shape.  */
  atexit (tui_exit);

  tui_initialize_static_data ();

  tui_initialize_io ();
  tui_initialize_readline ();

  return NULL;
}