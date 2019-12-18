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
struct mtk_eth {int dummy; } ;

/* Variables and functions */
 int mtk_ppe_debugfs_init (struct mtk_eth*) ; 
 int mtk_ppe_start (struct mtk_eth*) ; 

int mtk_ppe_probe(struct mtk_eth *eth)
{
	int err;

	err = mtk_ppe_start(eth);
	if (err)
		return err;

	err = mtk_ppe_debugfs_init(eth);
	if (err)
		return err;

	return 0;
}