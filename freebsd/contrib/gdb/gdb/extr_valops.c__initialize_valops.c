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
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auto_abandon ; 
 int /*<<< orphan*/  class_support ; 
 int overload_resolution ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_boolean ; 

void
_initialize_valops (void)
{
#if 0
  add_show_from_set
    (add_set_cmd ("abandon", class_support, var_boolean, (char *) &auto_abandon,
		  "Set automatic abandonment of expressions upon failure.",
		  &setlist),
     &showlist);
#endif

  add_show_from_set
    (add_set_cmd ("overload-resolution", class_support, var_boolean, (char *) &overload_resolution,
		  "Set overload resolution in evaluating C++ functions.",
		  &setlist),
     &showlist);
  overload_resolution = 1;
}