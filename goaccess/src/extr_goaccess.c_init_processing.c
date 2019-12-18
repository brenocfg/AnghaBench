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
struct TYPE_2__ {scalar_t__ load_from_disk; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  init_storage () ; 
 int /*<<< orphan*/  set_general_stats () ; 
 int /*<<< orphan*/  set_spec_date_format () ; 
 int /*<<< orphan*/  verify_panels () ; 

__attribute__((used)) static void
init_processing (void)
{
  /* perform some additional checks before parsing panels */
  verify_panels ();
  /* initialize storage */
  init_storage ();
  if (conf.load_from_disk)
    set_general_stats ();
  set_spec_date_format ();
}