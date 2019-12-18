#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* priv_p ;
struct TYPE_3__ {int flowsets_count; int /*<<< orphan*/ * v9_flowsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NETFLOW_GENERAL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ng_netflow_v9_cache_flush(priv_p priv)
{
	int i;

	/* Free flowsets*/
	for (i = 0; i < priv->flowsets_count; i++)
		free(priv->v9_flowsets[i], M_NETFLOW_GENERAL);
}