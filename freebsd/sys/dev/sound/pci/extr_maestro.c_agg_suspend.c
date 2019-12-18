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
struct agg_info {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGG_WR (struct agg_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_POWERSTATE_D3 ; 
 int /*<<< orphan*/  PORT_HOSTINT_CTRL ; 
 int /*<<< orphan*/  agg_lock (struct agg_info*) ; 
 int /*<<< orphan*/  agg_power (struct agg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agg_unlock (struct agg_info*) ; 
 struct agg_info* pcm_getdevinfo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
agg_suspend(device_t dev)
{
	struct agg_info *ess = pcm_getdevinfo(dev);

	AGG_WR(ess, PORT_HOSTINT_CTRL, 0, 2);
	agg_lock(ess);
	agg_power(ess, PCI_POWERSTATE_D3);
	agg_unlock(ess);

	return 0;
}