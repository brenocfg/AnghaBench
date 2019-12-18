#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int rx_wsize; int tx_wsize; int /*<<< orphan*/  maxio; int /*<<< orphan*/  timeout; int /*<<< orphan*/  in_use; } ;
struct TYPE_3__ {int /*<<< orphan*/  icr; } ;

/* Variables and functions */
#define  DSP56K_DEV_56001 128 
 int /*<<< orphan*/  DSP56K_ICR_HF0 ; 
 int /*<<< orphan*/  DSP56K_ICR_HF1 ; 
 int /*<<< orphan*/  DSP56K_RX_INT_OFF ; 
 int /*<<< orphan*/  DSP56K_TX_INT_OFF ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  MAXIO ; 
 int /*<<< orphan*/  TIMEOUT ; 
 TYPE_2__ dsp56k ; 
 TYPE_1__ dsp56k_host_interface ; 
 int /*<<< orphan*/  dsp56k_mutex ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsp56k_open(struct inode *inode, struct file *file)
{
	int dev = iminor(inode) & 0x0f;
	int ret = 0;

	mutex_lock(&dsp56k_mutex);
	switch(dev)
	{
	case DSP56K_DEV_56001:

		if (test_and_set_bit(0, &dsp56k.in_use)) {
			ret = -EBUSY;
			goto out;
		}

		dsp56k.timeout = TIMEOUT;
		dsp56k.maxio = MAXIO;
		dsp56k.rx_wsize = dsp56k.tx_wsize = 4; 

		DSP56K_TX_INT_OFF;
		DSP56K_RX_INT_OFF;

		/* Zero host flags */
		dsp56k_host_interface.icr &= ~DSP56K_ICR_HF0;
		dsp56k_host_interface.icr &= ~DSP56K_ICR_HF1;

		break;

	default:
		ret = -ENODEV;
	}
out:
	mutex_unlock(&dsp56k_mutex);
	return ret;
}