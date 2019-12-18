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
 int /*<<< orphan*/  mtk_ppe_stop (struct mtk_eth*) ; 

void mtk_ppe_remove(struct mtk_eth *eth)
{
	mtk_ppe_stop(eth);
}