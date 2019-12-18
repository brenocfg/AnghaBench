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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOW_SENSOR_INDEX ; 
 int /*<<< orphan*/  EPOW_SENSOR_TOKEN ; 
 int /*<<< orphan*/  ERR_TYPE_RTAS_LOG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RTAS_EPOW_WARNING ; 
 int /*<<< orphan*/  RTAS_VECTOR_EXTERNAL_INTERRUPT ; 
 int /*<<< orphan*/  __pa (scalar_t__*) ; 
 int /*<<< orphan*/  log_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ras_check_exception_token ; 
 scalar_t__ ras_log_buf ; 
 int /*<<< orphan*/  ras_log_buf_lock ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_get_error_log_max () ; 
 int rtas_get_sensor_fast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtas_parse_epow_errlog (struct rtas_error_log*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virq_to_hw (int) ; 

__attribute__((used)) static irqreturn_t ras_epow_interrupt(int irq, void *dev_id)
{
	int status;
	int state;
	int critical;

	status = rtas_get_sensor_fast(EPOW_SENSOR_TOKEN, EPOW_SENSOR_INDEX,
				      &state);

	if (state > 3)
		critical = 1;		/* Time Critical */
	else
		critical = 0;

	spin_lock(&ras_log_buf_lock);

	status = rtas_call(ras_check_exception_token, 6, 1, NULL,
			   RTAS_VECTOR_EXTERNAL_INTERRUPT,
			   virq_to_hw(irq),
			   RTAS_EPOW_WARNING,
			   critical, __pa(&ras_log_buf),
				rtas_get_error_log_max());

	log_error(ras_log_buf, ERR_TYPE_RTAS_LOG, 0);

	rtas_parse_epow_errlog((struct rtas_error_log *)ras_log_buf);

	spin_unlock(&ras_log_buf_lock);
	return IRQ_HANDLED;
}