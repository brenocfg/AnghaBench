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
typedef  int /*<<< orphan*/  tracking ;
struct TYPE_2__ {char* dst; } ;
struct tracking {int matches; char const* src; int /*<<< orphan*/  remote; TYPE_1__ spec; } ;
typedef  enum branch_track { ____Placeholder_branch_track } branch_track ;

/* Variables and functions */
 int BRANCH_CONFIG_VERBOSE ; 
#define  BRANCH_TRACK_ALWAYS 130 
#define  BRANCH_TRACK_EXPLICIT 129 
#define  BRANCH_TRACK_OVERRIDE 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  find_tracked_branch ; 
 scalar_t__ for_each_remote (int /*<<< orphan*/ ,struct tracking*) ; 
 int /*<<< orphan*/  free (char const*) ; 
 scalar_t__ install_branch_config (int,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  memset (struct tracking*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_tracking(const char *new_ref, const char *orig_ref,
			   enum branch_track track, int quiet)
{
	struct tracking tracking;
	int config_flags = quiet ? 0 : BRANCH_CONFIG_VERBOSE;

	memset(&tracking, 0, sizeof(tracking));
	tracking.spec.dst = (char *)orig_ref;
	if (for_each_remote(find_tracked_branch, &tracking))
		return;

	if (!tracking.matches)
		switch (track) {
		case BRANCH_TRACK_ALWAYS:
		case BRANCH_TRACK_EXPLICIT:
		case BRANCH_TRACK_OVERRIDE:
			break;
		default:
			return;
		}

	if (tracking.matches > 1)
		die(_("Not tracking: ambiguous information for ref %s"),
		    orig_ref);

	if (install_branch_config(config_flags, new_ref, tracking.remote,
			      tracking.src ? tracking.src : orig_ref) < 0)
		exit(-1);

	free(tracking.src);
}