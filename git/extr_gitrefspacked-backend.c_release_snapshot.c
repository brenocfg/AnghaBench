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
struct snapshot {int /*<<< orphan*/  validity; int /*<<< orphan*/  referrers; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_snapshot_buffer (struct snapshot*) ; 
 int /*<<< orphan*/  free (struct snapshot*) ; 
 int /*<<< orphan*/  stat_validity_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int release_snapshot(struct snapshot *snapshot)
{
	if (!--snapshot->referrers) {
		stat_validity_clear(&snapshot->validity);
		clear_snapshot_buffer(snapshot);
		free(snapshot);
		return 1;
	} else {
		return 0;
	}
}