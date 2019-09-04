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
struct TYPE_2__ {int /*<<< orphan*/  color_scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  MONOCHROME ; 
 int /*<<< orphan*/  MONOKAI ; 
 int /*<<< orphan*/  STD_GREEN ; 
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free_color_lists () ; 
 int /*<<< orphan*/  init_colors (int) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static void
scheme_chosen (const char *name)
{
  int force = 0;

  free_color_lists ();
  if (strcmp ("Green", name) == 0) {
    conf.color_scheme = STD_GREEN;
    force = 1;
  } else if (strcmp ("Monochrome", name) == 0) {
    conf.color_scheme = MONOCHROME;
    force = 1;
  } else if (strcmp ("Monokai", name) == 0) {
    conf.color_scheme = MONOKAI;
    force = 1;
  } else if (strcmp ("Custom Scheme", name) == 0) {
    force = 0;
  }
  init_colors (force);
}