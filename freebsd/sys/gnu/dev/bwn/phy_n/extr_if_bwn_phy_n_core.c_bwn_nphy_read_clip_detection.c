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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_C1_CLIP1THRES ; 
 int /*<<< orphan*/  BWN_NPHY_C2_CLIP1THRES ; 
 int /*<<< orphan*/  BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwn_nphy_read_clip_detection(struct bwn_mac *mac, uint16_t *clip_st)
{
	clip_st[0] = BWN_PHY_READ(mac, BWN_NPHY_C1_CLIP1THRES);
	clip_st[1] = BWN_PHY_READ(mac, BWN_NPHY_C2_CLIP1THRES);
}