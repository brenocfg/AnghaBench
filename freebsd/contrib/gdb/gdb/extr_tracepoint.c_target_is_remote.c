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
struct TYPE_2__ {scalar_t__ to_shortname; } ;

/* Variables and functions */
 TYPE_1__ current_target ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int
target_is_remote (void)
{
  if (current_target.to_shortname &&
      strcmp (current_target.to_shortname, "remote") == 0)
    return 1;
  else
    return 0;
}