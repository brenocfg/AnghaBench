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
struct TYPE_2__ {int completion_status; int /*<<< orphan*/  val; int /*<<< orphan*/  ae; int /*<<< orphan*/  cmp; int /*<<< orphan*/  con; int /*<<< orphan*/  extended_status; } ;
typedef  TYPE_1__ sli4_mcqe_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t
sli_cqe_mq(void *buf)
{
	sli4_mcqe_t	*mcqe = buf;

	/*
	 * Firmware can split mbx completions into two MCQEs: first with only
	 * the "consumed" bit set and a second with the "complete" bit set.
	 * Thus, ignore MCQE unless "complete" is set.
	 */
	if (!mcqe->cmp) {
		return -2;
	}

	if (mcqe->completion_status) {
		ocs_log_debug(NULL, "bad status (cmpl=%#x ext=%#x con=%d cmp=%d ae=%d val=%d)\n",
				mcqe->completion_status,
				mcqe->extended_status,
				mcqe->con,
				mcqe->cmp,
				mcqe->ae,
				mcqe->val);
	}

	return mcqe->completion_status;
}