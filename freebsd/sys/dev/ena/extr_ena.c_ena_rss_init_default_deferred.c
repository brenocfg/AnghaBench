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
struct ena_adapter {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ALERT ; 
 int /*<<< orphan*/  ENA_FLAG_CLEAR_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_RSS_ACTIVE ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ *) ; 
 struct ena_adapter* devclass_get_softc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ena_rss_init_default (struct ena_adapter*) ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
ena_rss_init_default_deferred(void *arg)
{
	struct ena_adapter *adapter;
	devclass_t dc;
	int max;
	int rc;

	dc = devclass_find("ena");
	if (unlikely(dc == NULL)) {
		ena_trace(ENA_ALERT, "No devclass ena\n");
		return;
	}

	max = devclass_get_maxunit(dc);
	while (max-- >= 0) {
		adapter = devclass_get_softc(dc, max);
		if (adapter != NULL) {
			rc = ena_rss_init_default(adapter);
			ENA_FLAG_SET_ATOMIC(ENA_FLAG_RSS_ACTIVE, adapter);
			if (unlikely(rc != 0)) {
				device_printf(adapter->pdev,
				    "WARNING: RSS was not properly initialized,"
				    " it will affect bandwidth\n");
				ENA_FLAG_CLEAR_ATOMIC(ENA_FLAG_RSS_ACTIVE, adapter);
			}
		}
	}
}