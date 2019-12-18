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
 int /*<<< orphan*/  ERR_TYPE_RTAS_LOG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RTAS_INTERNAL_ERROR ; 
 scalar_t__ RTAS_SEVERITY_ERROR_SYNC ; 
 int /*<<< orphan*/  RTAS_VECTOR_EXTERNAL_INTERRUPT ; 
 int /*<<< orphan*/  __pa (scalar_t__*) ; 
 int /*<<< orphan*/  emergency_sync () ; 
 int /*<<< orphan*/  kernel_power_off () ; 
 int /*<<< orphan*/  log_error (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  ras_check_exception_token ; 
 scalar_t__ ras_log_buf ; 
 int /*<<< orphan*/  ras_log_buf_lock ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtas_error_severity (struct rtas_error_log*) ; 
 int /*<<< orphan*/  rtas_get_error_log_max () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virq_to_hw (int) ; 

__attribute__((used)) static irqreturn_t ras_error_interrupt(int irq, void *dev_id)
{
	struct rtas_error_log *rtas_elog;
	int status;
	int fatal;

	spin_lock(&ras_log_buf_lock);

	status = rtas_call(ras_check_exception_token, 6, 1, NULL,
			   RTAS_VECTOR_EXTERNAL_INTERRUPT,
			   virq_to_hw(irq),
			   RTAS_INTERNAL_ERROR, 1 /* Time Critical */,
			   __pa(&ras_log_buf),
				rtas_get_error_log_max());

	rtas_elog = (struct rtas_error_log *)ras_log_buf;

	if (status == 0 &&
	    rtas_error_severity(rtas_elog) >= RTAS_SEVERITY_ERROR_SYNC)
		fatal = 1;
	else
		fatal = 0;

	/* format and print the extended information */
	log_error(ras_log_buf, ERR_TYPE_RTAS_LOG, fatal);

	if (fatal) {
		pr_emerg("Fatal hardware error detected. Check RTAS error"
			 " log for details. Powering off immediately\n");
		emergency_sync();
		kernel_power_off();
	} else {
		pr_err("Recoverable hardware error detected\n");
	}

	spin_unlock(&ras_log_buf_lock);
	return IRQ_HANDLED;
}