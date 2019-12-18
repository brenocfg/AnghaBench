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
struct bwn_phy_n {int dummy; } ;
struct TYPE_2__ {struct bwn_phy_n* phy_n; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct bwn_phy_n* malloc (int,int /*<<< orphan*/ ,int) ; 

int
bwn_nphy_op_allocate(struct bwn_mac *mac)
{
	struct bwn_phy_n *nphy;

	nphy = malloc(sizeof(*nphy), M_DEVBUF, M_ZERO | M_NOWAIT);
	if (!nphy)
		return -ENOMEM;

	mac->mac_phy.phy_n = nphy;

	return 0;
}