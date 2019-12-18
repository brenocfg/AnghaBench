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
typedef  int /*<<< orphan*/  uint64_t ;
struct g_bde_key {int /*<<< orphan*/  zone_cont; int /*<<< orphan*/  zone_width; int /*<<< orphan*/  media_width; } ;

/* Variables and functions */

uint64_t
g_bde_max_sector(struct g_bde_key *kp)
{
	uint64_t maxsect;

	maxsect = kp->media_width;
	maxsect /= kp->zone_width;
	maxsect *= kp->zone_cont;
	return (maxsect);
}