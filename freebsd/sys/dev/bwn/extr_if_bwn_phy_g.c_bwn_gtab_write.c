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
typedef  scalar_t__ uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_GTABCTL ; 
 int /*<<< orphan*/  BWN_PHY_GTABDATA ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
bwn_gtab_write(struct bwn_mac *mac, uint16_t table, uint16_t offset,
    uint16_t value)
{

	BWN_PHY_WRITE(mac, BWN_PHY_GTABCTL, table + offset);
	BWN_PHY_WRITE(mac, BWN_PHY_GTABDATA, value);
}