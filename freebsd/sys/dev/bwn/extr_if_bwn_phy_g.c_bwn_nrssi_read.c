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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_NRSSI_CTRL ; 
 int /*<<< orphan*/  BWN_PHY_NRSSI_DATA ; 
 scalar_t__ BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int16_t
bwn_nrssi_read(struct bwn_mac *mac, uint16_t offset)
{

	BWN_PHY_WRITE(mac, BWN_PHY_NRSSI_CTRL, offset);
	return ((int16_t)BWN_PHY_READ(mac, BWN_PHY_NRSSI_DATA));
}