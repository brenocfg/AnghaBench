#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  cfg_section_t ;
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/ * x_value; } ;
typedef  TYPE_1__ cfg_option_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ option_state_cyclic ; 
 scalar_t__ option_state_expanded ; 
 scalar_t__ option_state_needs_expanding ; 

__attribute__((used)) static svn_boolean_t
rmex_callback(void *baton, cfg_section_t *section, cfg_option_t *option)
{
  /* Only reset the expansion state if the value actually contains
     variable expansions. */
  if (   (option->state == option_state_expanded && option->x_value != NULL)
      || option->state == option_state_cyclic)
    {
      option->x_value = NULL;
      option->state = option_state_needs_expanding;
    }

  return FALSE;
}