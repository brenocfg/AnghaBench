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
struct lmac {int last_link; int last_duplex; int last_speed; int link_up; int /*<<< orphan*/  check_link; scalar_t__ is_sgmii; int /*<<< orphan*/  lmacid; int /*<<< orphan*/  phy_if_dev; } ;

/* Variables and functions */
 int LMAC_MEDIA_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  bgx_sgmii_change_link_state (struct lmac*) ; 
 int /*<<< orphan*/  bgx_xaui_check_link (struct lmac*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct lmac*) ; 
 int hz ; 

__attribute__((used)) static void
bgx_lmac_handler(void *arg)
{
	struct lmac *lmac;
	int link, duplex, speed;
	int link_changed = 0;
	int err;

	lmac = (struct lmac *)arg;

	err = LMAC_MEDIA_STATUS(lmac->phy_if_dev, lmac->lmacid,
	    &link, &duplex, &speed);
	if (err != 0)
		goto out;

	if (!link && lmac->last_link)
		link_changed = -1;

	if (link &&
	    (lmac->last_duplex != duplex ||
	     lmac->last_link != link ||
	     lmac->last_speed != speed)) {
			link_changed = 1;
	}

	lmac->last_link = link;
	lmac->last_speed = speed;
	lmac->last_duplex = duplex;

	if (!link_changed)
		goto out;

	if (link_changed > 0)
		lmac->link_up = true;
	else
		lmac->link_up = false;

	if (lmac->is_sgmii)
		bgx_sgmii_change_link_state(lmac);
	else
		bgx_xaui_check_link(lmac);

out:
	callout_reset(&lmac->check_link, hz * 2, bgx_lmac_handler, lmac);
}