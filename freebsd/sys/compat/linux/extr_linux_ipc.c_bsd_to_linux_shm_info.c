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
struct shm_info {int /*<<< orphan*/  swap_successes; int /*<<< orphan*/  swap_attempts; int /*<<< orphan*/  shm_swp; int /*<<< orphan*/  shm_rss; int /*<<< orphan*/  shm_tot; int /*<<< orphan*/  used_ids; } ;
struct l_shm_info {int /*<<< orphan*/  swap_successes; int /*<<< orphan*/  swap_attempts; int /*<<< orphan*/  shm_swp; int /*<<< orphan*/  shm_rss; int /*<<< orphan*/  shm_tot; int /*<<< orphan*/  used_ids; } ;

/* Variables and functions */

__attribute__((used)) static void
bsd_to_linux_shm_info( struct shm_info *bpp, struct l_shm_info *lpp)
{

	lpp->used_ids = bpp->used_ids;
	lpp->shm_tot = bpp->shm_tot;
	lpp->shm_rss = bpp->shm_rss;
	lpp->shm_swp = bpp->shm_swp;
	lpp->swap_attempts = bpp->swap_attempts;
	lpp->swap_successes = bpp->swap_successes;
}