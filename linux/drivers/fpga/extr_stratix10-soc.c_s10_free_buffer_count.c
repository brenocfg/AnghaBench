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
typedef  size_t uint ;
struct s10_priv {TYPE_1__* svc_bufs; } ;
struct fpga_manager {struct s10_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 size_t NUM_SVC_BUFS ; 

__attribute__((used)) static uint s10_free_buffer_count(struct fpga_manager *mgr)
{
	struct s10_priv *priv = mgr->priv;
	uint num_free = 0;
	uint i;

	for (i = 0; i < NUM_SVC_BUFS; i++)
		if (!priv->svc_bufs[i].buf)
			num_free++;

	return num_free;
}