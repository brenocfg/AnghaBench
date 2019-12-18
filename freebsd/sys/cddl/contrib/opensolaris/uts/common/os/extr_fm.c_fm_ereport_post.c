#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sysevent_id_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  evchan_t ;
struct TYPE_4__ {int /*<<< orphan*/  ui64; } ;
struct TYPE_5__ {TYPE_1__ value; } ;
struct TYPE_6__ {TYPE_2__ erpt_dropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDI_SLEEP ; 
 int /*<<< orphan*/  EC_DEV_STATUS ; 
 int /*<<< orphan*/  EC_FM ; 
 size_t ERPT_DATA_SZ ; 
 int /*<<< orphan*/  ESC_DEV_DLE ; 
 int /*<<< orphan*/  ESC_FM_ERROR ; 
 int EVCH_CREAT ; 
 int EVCH_HOLD_PEND ; 
 int /*<<< orphan*/  FM_ERROR_CHAN ; 
 int /*<<< orphan*/  FM_PUB ; 
 int /*<<< orphan*/  NV_ENCODE_NATIVE ; 
 int /*<<< orphan*/  SUNW_VENDOR ; 
 int /*<<< orphan*/  atomic_inc_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddi_log_sysevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ erpt_kstat_data ; 
 int /*<<< orphan*/  nvlist_size (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysevent_evc_bind (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ sysevent_evc_publish (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sysevent_evc_unbind (int /*<<< orphan*/ *) ; 

void
fm_ereport_post(nvlist_t *ereport, int evc_flag)
{
	size_t nvl_size = 0;
	evchan_t *error_chan;
	sysevent_id_t eid;

	(void) nvlist_size(ereport, &nvl_size, NV_ENCODE_NATIVE);
	if (nvl_size > ERPT_DATA_SZ || nvl_size == 0) {
		atomic_inc_64(&erpt_kstat_data.erpt_dropped.value.ui64);
		return;
	}

#ifdef illumos
	if (sysevent_evc_bind(FM_ERROR_CHAN, &error_chan,
	    EVCH_CREAT|EVCH_HOLD_PEND) != 0) {
		atomic_inc_64(&erpt_kstat_data.erpt_dropped.value.ui64);
		return;
	}

	if (sysevent_evc_publish(error_chan, EC_FM, ESC_FM_ERROR,
	    SUNW_VENDOR, FM_PUB, ereport, evc_flag) != 0) {
		atomic_inc_64(&erpt_kstat_data.erpt_dropped.value.ui64);
		(void) sysevent_evc_unbind(error_chan);
		return;
	}
	(void) sysevent_evc_unbind(error_chan);
#else
	(void) ddi_log_sysevent(NULL, SUNW_VENDOR, EC_DEV_STATUS,
	    ESC_DEV_DLE, ereport, &eid, DDI_SLEEP);
#endif
}