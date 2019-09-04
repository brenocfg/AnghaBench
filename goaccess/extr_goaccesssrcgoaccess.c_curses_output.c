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
struct TYPE_2__ {int /*<<< orphan*/  skip_term_resolver; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocate_data () ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  gdns_thread_create () ; 
 int /*<<< orphan*/  get_keys () ; 
 int /*<<< orphan*/  render_screens () ; 

__attribute__((used)) static void
curses_output (void)
{
  allocate_data ();
  if (!conf.skip_term_resolver)
    gdns_thread_create ();

  render_screens ();
  /* will loop in here */
  get_keys ();
}