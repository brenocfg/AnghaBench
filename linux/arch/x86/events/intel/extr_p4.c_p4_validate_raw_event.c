#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  config; } ;
struct perf_event {TYPE_1__ attr; } ;
struct TYPE_6__ {unsigned int escr_emask; scalar_t__ shared; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int EINVAL ; 
 unsigned int P4_ESCR_EVENTMASK_MASK ; 
 int /*<<< orphan*/  P4_PEBS_CONFIG_ENABLE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ p4_config_pebs_has (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int p4_config_unpack_escr (int /*<<< orphan*/ ) ; 
 unsigned int p4_config_unpack_event (int /*<<< orphan*/ ) ; 
 unsigned int p4_config_unpack_metric (int /*<<< orphan*/ ) ; 
 TYPE_2__* p4_event_bind_map ; 
 int /*<<< orphan*/  p4_event_match_cpu_model (unsigned int) ; 
 scalar_t__ p4_ht_active () ; 
 TYPE_2__* p4_pebs_bind_map ; 
 scalar_t__ perf_paranoid_cpu () ; 

__attribute__((used)) static int p4_validate_raw_event(struct perf_event *event)
{
	unsigned int v, emask;

	/* User data may have out-of-bound event index */
	v = p4_config_unpack_event(event->attr.config);
	if (v >= ARRAY_SIZE(p4_event_bind_map))
		return -EINVAL;

	/* It may be unsupported: */
	if (!p4_event_match_cpu_model(v))
		return -EINVAL;

	/*
	 * NOTE: P4_CCCR_THREAD_ANY has not the same meaning as
	 * in Architectural Performance Monitoring, it means not
	 * on _which_ logical cpu to count but rather _when_, ie it
	 * depends on logical cpu state -- count event if one cpu active,
	 * none, both or any, so we just allow user to pass any value
	 * desired.
	 *
	 * In turn we always set Tx_OS/Tx_USR bits bound to logical
	 * cpu without their propagation to another cpu
	 */

	/*
	 * if an event is shared across the logical threads
	 * the user needs special permissions to be able to use it
	 */
	if (p4_ht_active() && p4_event_bind_map[v].shared) {
		if (perf_paranoid_cpu() && !capable(CAP_SYS_ADMIN))
			return -EACCES;
	}

	/* ESCR EventMask bits may be invalid */
	emask = p4_config_unpack_escr(event->attr.config) & P4_ESCR_EVENTMASK_MASK;
	if (emask & ~p4_event_bind_map[v].escr_emask)
		return -EINVAL;

	/*
	 * it may have some invalid PEBS bits
	 */
	if (p4_config_pebs_has(event->attr.config, P4_PEBS_CONFIG_ENABLE))
		return -EINVAL;

	v = p4_config_unpack_metric(event->attr.config);
	if (v >= ARRAY_SIZE(p4_pebs_bind_map))
		return -EINVAL;

	return 0;
}