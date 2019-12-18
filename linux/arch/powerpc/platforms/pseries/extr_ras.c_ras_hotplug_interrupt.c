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
struct rtas_error_log {int dummy; } ;
struct pseries_hp_errorlog {scalar_t__ resource; } ;
struct pseries_errorlog {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_TYPE_RTAS_LOG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PSERIES_ELOG_SECT_ID_HOTPLUG ; 
 scalar_t__ PSERIES_HP_ELOG_RESOURCE_CPU ; 
 scalar_t__ PSERIES_HP_ELOG_RESOURCE_MEM ; 
 scalar_t__ PSERIES_HP_ELOG_RESOURCE_PMEM ; 
 int /*<<< orphan*/  RTAS_HOTPLUG_EVENTS ; 
 int /*<<< orphan*/  RTAS_VECTOR_EXTERNAL_INTERRUPT ; 
 int /*<<< orphan*/  __pa (scalar_t__*) ; 
 struct pseries_errorlog* get_pseries_errorlog (struct rtas_error_log*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_hotplug_event (struct pseries_hp_errorlog*) ; 
 int /*<<< orphan*/  ras_check_exception_token ; 
 scalar_t__ ras_log_buf ; 
 int /*<<< orphan*/  ras_log_buf_lock ; 
 int /*<<< orphan*/  rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_get_error_log_max () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virq_to_hw (int) ; 

__attribute__((used)) static irqreturn_t ras_hotplug_interrupt(int irq, void *dev_id)
{
	struct pseries_errorlog *pseries_log;
	struct pseries_hp_errorlog *hp_elog;

	spin_lock(&ras_log_buf_lock);

	rtas_call(ras_check_exception_token, 6, 1, NULL,
		  RTAS_VECTOR_EXTERNAL_INTERRUPT, virq_to_hw(irq),
		  RTAS_HOTPLUG_EVENTS, 0, __pa(&ras_log_buf),
		  rtas_get_error_log_max());

	pseries_log = get_pseries_errorlog((struct rtas_error_log *)ras_log_buf,
					   PSERIES_ELOG_SECT_ID_HOTPLUG);
	hp_elog = (struct pseries_hp_errorlog *)pseries_log->data;

	/*
	 * Since PCI hotplug is not currently supported on pseries, put PCI
	 * hotplug events on the ras_log_buf to be handled by rtas_errd.
	 */
	if (hp_elog->resource == PSERIES_HP_ELOG_RESOURCE_MEM ||
	    hp_elog->resource == PSERIES_HP_ELOG_RESOURCE_CPU ||
	    hp_elog->resource == PSERIES_HP_ELOG_RESOURCE_PMEM)
		queue_hotplug_event(hp_elog);
	else
		log_error(ras_log_buf, ERR_TYPE_RTAS_LOG, 0);

	spin_unlock(&ras_log_buf_lock);
	return IRQ_HANDLED;
}