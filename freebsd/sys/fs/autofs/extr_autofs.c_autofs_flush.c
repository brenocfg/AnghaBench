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
struct autofs_mount {int /*<<< orphan*/  am_mountpoint; TYPE_1__* am_root; } ;
struct TYPE_2__ {int an_cached; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_DEBUG (char*,int /*<<< orphan*/ ) ; 

void
autofs_flush(struct autofs_mount *amp)
{

	/*
	 * XXX: This will do for now, but ideally we should iterate
	 * 	over all the nodes.
	 */
	amp->am_root->an_cached = false;
	AUTOFS_DEBUG("%s flushed", amp->am_mountpoint);
}