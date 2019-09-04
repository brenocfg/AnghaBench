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
struct TYPE_3__ {int received_objects; int total_objects; } ;
typedef  TYPE_1__ git_indexer_progress ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

__attribute__((used)) static int cancel_at_half(const git_indexer_progress *stats, void *payload)
{
	GIT_UNUSED(payload);

	if (stats->received_objects > (stats->total_objects/2))
		return 4321;
	return 0;
}