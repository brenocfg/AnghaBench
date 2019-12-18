#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; int /*<<< orphan*/  data0; } ;
typedef  TYPE_1__ pmi_message_t ;
struct TYPE_5__ {int /*<<< orphan*/  msg_mutex; int /*<<< orphan*/ * completion; int /*<<< orphan*/  pmi_spinlock; scalar_t__ pmi_reg; TYPE_1__ msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  PMI_TIMEOUT ; 
 scalar_t__ PMI_WRITE_DATA0 ; 
 scalar_t__ PMI_WRITE_DATA1 ; 
 scalar_t__ PMI_WRITE_DATA2 ; 
 scalar_t__ PMI_WRITE_TYPE ; 
 int /*<<< orphan*/  completion ; 
 TYPE_3__* data ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int pmi_send_message(pmi_message_t msg)
{
	unsigned long flags;
	DECLARE_COMPLETION_ONSTACK(completion);

	if (!data)
		return -ENODEV;

	mutex_lock(&data->msg_mutex);

	data->msg = msg;
	pr_debug("pmi_send_message: msg is %08x\n", *(u32*)&msg);

	data->completion = &completion;

	spin_lock_irqsave(&data->pmi_spinlock, flags);
	iowrite8(msg.data0, data->pmi_reg + PMI_WRITE_DATA0);
	iowrite8(msg.data1, data->pmi_reg + PMI_WRITE_DATA1);
	iowrite8(msg.data2, data->pmi_reg + PMI_WRITE_DATA2);
	iowrite8(msg.type, data->pmi_reg + PMI_WRITE_TYPE);
	spin_unlock_irqrestore(&data->pmi_spinlock, flags);

	pr_debug("pmi_send_message: wait for completion\n");

	wait_for_completion_interruptible_timeout(data->completion,
						  PMI_TIMEOUT);

	data->completion = NULL;

	mutex_unlock(&data->msg_mutex);

	return 0;
}