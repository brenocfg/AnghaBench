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
struct uniphier_mdmac_desc {int dummy; } ;
struct uniphier_mdmac_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uniphier_mdmac_handle (struct uniphier_mdmac_chan*,struct uniphier_mdmac_desc*) ; 
 struct uniphier_mdmac_desc* uniphier_mdmac_next_desc (struct uniphier_mdmac_chan*) ; 

__attribute__((used)) static void uniphier_mdmac_start(struct uniphier_mdmac_chan *mc)
{
	struct uniphier_mdmac_desc *md;

	md = uniphier_mdmac_next_desc(mc);
	if (md)
		uniphier_mdmac_handle(mc, md);
}