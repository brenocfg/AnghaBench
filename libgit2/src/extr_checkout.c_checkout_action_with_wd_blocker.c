#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_index_entry ;
struct TYPE_5__ {int status; } ;
typedef  TYPE_1__ git_diff_delta ;
typedef  int /*<<< orphan*/  checkout_data ;

/* Variables and functions */
 int CHECKOUT_ACTION_IF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CHECKOUT_ACTION__NONE ; 
 int /*<<< orphan*/  CONFLICT ; 
 int /*<<< orphan*/  FORCE ; 
 int /*<<< orphan*/  GIT_CHECKOUT_NOTIFY_DIRTY ; 
#define  GIT_DELTA_ADDED 132 
#define  GIT_DELTA_DELETED 131 
#define  GIT_DELTA_MODIFIED 130 
#define  GIT_DELTA_TYPECHANGE 129 
#define  GIT_DELTA_UNMODIFIED 128 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  REMOVE ; 
 int /*<<< orphan*/  REMOVE_AND_UPDATE ; 
 int checkout_action_common (int*,int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  checkout_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int checkout_action_with_wd_blocker(
	int *action,
	checkout_data *data,
	const git_diff_delta *delta,
	const git_index_entry *wd)
{
	*action = CHECKOUT_ACTION__NONE;

	switch (delta->status) {
	case GIT_DELTA_UNMODIFIED:
		/* should show delta as dirty / deleted */
		GIT_ERROR_CHECK_ERROR(
			checkout_notify(data, GIT_CHECKOUT_NOTIFY_DIRTY, delta, wd) );
		*action = CHECKOUT_ACTION_IF(FORCE, REMOVE_AND_UPDATE, NONE);
		break;
	case GIT_DELTA_ADDED:
	case GIT_DELTA_MODIFIED:
		*action = CHECKOUT_ACTION_IF(FORCE, REMOVE_AND_UPDATE, CONFLICT);
		break;
	case GIT_DELTA_DELETED:
		*action = CHECKOUT_ACTION_IF(FORCE, REMOVE, CONFLICT);
		break;
	case GIT_DELTA_TYPECHANGE:
		/* not 100% certain about this... */
		*action = CHECKOUT_ACTION_IF(FORCE, REMOVE_AND_UPDATE, CONFLICT);
		break;
	default: /* impossible */
		break;
	}

	return checkout_action_common(action, data, delta, wd);
}