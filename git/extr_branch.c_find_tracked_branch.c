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
struct TYPE_2__ {int /*<<< orphan*/ * src; } ;
struct tracking {int matches; TYPE_1__ spec; int /*<<< orphan*/ * src; int /*<<< orphan*/  remote; } ;
struct remote {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_find_tracking (struct remote*,TYPE_1__*) ; 

__attribute__((used)) static int find_tracked_branch(struct remote *remote, void *priv)
{
	struct tracking *tracking = priv;

	if (!remote_find_tracking(remote, &tracking->spec)) {
		if (++tracking->matches == 1) {
			tracking->src = tracking->spec.src;
			tracking->remote = remote->name;
		} else {
			free(tracking->spec.src);
			FREE_AND_NULL(tracking->src);
		}
		tracking->spec.src = NULL;
	}

	return 0;
}