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
struct TYPE_2__ {int /*<<< orphan*/  device_list_mutex; int /*<<< orphan*/  connlist_mutex; int /*<<< orphan*/  close_conns_mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ISER_DBG (char*) ; 
 scalar_t__ icl_iser_ncons ; 
 int /*<<< orphan*/  icl_pdu_zone ; 
 int /*<<< orphan*/  icl_unregister (char*,int) ; 
 TYPE_1__ ig ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
icl_iser_unload(void)
{
	ISER_DBG("Removing iSER datamover...");

	if (icl_iser_ncons != 0)
		return (EBUSY);

	sx_destroy(&ig.close_conns_mutex);
	mtx_destroy(&ig.connlist_mutex);
	sx_destroy(&ig.device_list_mutex);

	icl_unregister("iser", true);

	uma_zdestroy(icl_pdu_zone);

	return (0);
}