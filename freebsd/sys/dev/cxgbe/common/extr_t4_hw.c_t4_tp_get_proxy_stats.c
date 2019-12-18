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
struct tp_proxy_stats {int /*<<< orphan*/  proxy; } ;
struct adapter {TYPE_1__* chip_params; } ;
struct TYPE_2__ {int nchan; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_MIB_TNL_LPBK_0 ; 
 int /*<<< orphan*/  t4_tp_mib_read (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void t4_tp_get_proxy_stats(struct adapter *adap, struct tp_proxy_stats *st,
    bool sleep_ok)
{
	int nchan = adap->chip_params->nchan;

	t4_tp_mib_read(adap, st->proxy, nchan, A_TP_MIB_TNL_LPBK_0, sleep_ok);
}