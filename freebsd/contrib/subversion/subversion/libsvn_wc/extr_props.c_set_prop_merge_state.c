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
typedef  char svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  ordering ;

/* Variables and functions */
#define  svn_wc_notify_state_changed 134 
#define  svn_wc_notify_state_conflicted 133 
#define  svn_wc_notify_state_inapplicable 132 
#define  svn_wc_notify_state_merged 131 
#define  svn_wc_notify_state_obstructed 130 
#define  svn_wc_notify_state_unchanged 129 
#define  svn_wc_notify_state_unknown 128 

__attribute__((used)) static void
set_prop_merge_state(svn_wc_notify_state_t *state,
                     svn_wc_notify_state_t new_value)
{
  static char ordering[] =
    { svn_wc_notify_state_unknown,
      svn_wc_notify_state_unchanged,
      svn_wc_notify_state_inapplicable,
      svn_wc_notify_state_changed,
      svn_wc_notify_state_merged,
      svn_wc_notify_state_obstructed,
      svn_wc_notify_state_conflicted };
  int state_pos = 0, i;

  if (! state)
    return;

  /* Find *STATE in our ordering */
  for (i = 0; i < sizeof(ordering); i++)
    {
      if (*state == ordering[i])
        {
          state_pos = i;
          break;
        }
    }

  /* Find NEW_VALUE in our ordering
   * We don't need to look further than where we found *STATE though:
   * If we find our value, it's order is too low.
   * If we don't find it, we'll want to set it, no matter its order.
   */

  for (i = 0; i <= state_pos; i++)
    {
      if (new_value == ordering[i])
        return;
    }

  *state = new_value;
}