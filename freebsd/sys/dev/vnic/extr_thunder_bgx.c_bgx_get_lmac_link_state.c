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
struct lmac {int /*<<< orphan*/  last_speed; int /*<<< orphan*/  last_duplex; int /*<<< orphan*/  link_up; } ;
struct bgx_link_status {int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  link_up; } ;
struct bgx {struct lmac* lmac; } ;

/* Variables and functions */
 int MAX_BGX_PER_CN88XX ; 
 struct bgx** bgx_vnic ; 

void
bgx_get_lmac_link_state(int node, int bgx_idx, int lmacid, void *status)
{
	struct bgx_link_status *link = (struct bgx_link_status *)status;
	struct bgx *bgx;
	struct lmac *lmac;

	bgx = bgx_vnic[(node * MAX_BGX_PER_CN88XX) + bgx_idx];
	if (bgx == NULL)
		return;

	lmac = &bgx->lmac[lmacid];
	link->link_up = lmac->link_up;
	link->duplex = lmac->last_duplex;
	link->speed = lmac->last_speed;
}