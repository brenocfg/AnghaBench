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
typedef  int /*<<< orphan*/  svn_wc_conflict_action_t ;
typedef  int /*<<< orphan*/  svn_client_conflict_t ;
struct TYPE_2__ {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 TYPE_1__* get_conflict_desc2_t (int /*<<< orphan*/ *) ; 

svn_wc_conflict_action_t
svn_client_conflict_get_incoming_change(svn_client_conflict_t *conflict)
{
  return get_conflict_desc2_t(conflict)->action;
}