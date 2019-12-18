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
typedef  enum action { ____Placeholder_action } action ;
struct TYPE_3__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int Fail ; 
 int Hold ; 
 int Ok ; 
 scalar_t__ PD_MAX_RETRIES ; 
 int /*<<< orphan*/  STAT_DRQ ; 
 int STAT_ERR ; 
 int Wait ; 
 int /*<<< orphan*/  do_pd_read_start ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pd_buf ; 
 TYPE_1__* pd_current ; 
 scalar_t__ pd_next_buf () ; 
 int /*<<< orphan*/  pd_ready () ; 
 scalar_t__ pd_retries ; 
 int /*<<< orphan*/  pd_timeout ; 
 int pd_wait_for (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  phase ; 
 int /*<<< orphan*/  pi_read_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum action do_pd_read_drq(void)
{
	if (!pd_ready() && !time_after_eq(jiffies, pd_timeout))
		return Hold;

	while (1) {
		if (pd_wait_for(pd_current, STAT_DRQ, "do_pd_read_drq") & STAT_ERR) {
			if (pd_retries < PD_MAX_RETRIES) {
				pd_retries++;
				phase = do_pd_read_start;
				return Wait;
			}
			return Fail;
		}
		pi_read_block(pd_current->pi, pd_buf, 512);
		if (pd_next_buf())
			break;
	}
	return Ok;
}