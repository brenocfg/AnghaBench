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
struct bwi_retry_lim {int /*<<< orphan*/  lgretry_fb; int /*<<< orphan*/  shretry_fb; int /*<<< orphan*/  lgretry; int /*<<< orphan*/  shretry; } ;
struct bwi_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_80211_MOBJ ; 
 int /*<<< orphan*/  BWI_80211_MOBJ_LGRETRY ; 
 int /*<<< orphan*/  BWI_80211_MOBJ_SHRETRY ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_LGRETEY_FB ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_SHRETRY_FB ; 
 int /*<<< orphan*/  MOBJ_WRITE_2 (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwi_mac_set_retry_lim(struct bwi_mac *mac, const struct bwi_retry_lim *lim)
{
	/* Short/Long retry limit */
	MOBJ_WRITE_2(mac, BWI_80211_MOBJ, BWI_80211_MOBJ_SHRETRY,
		     lim->shretry);
	MOBJ_WRITE_2(mac, BWI_80211_MOBJ, BWI_80211_MOBJ_LGRETRY,
		     lim->lgretry);

	/* Short/Long retry fallback limit */
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_SHRETRY_FB,
		     lim->shretry_fb);
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_LGRETEY_FB,
		     lim->lgretry_fb);
}