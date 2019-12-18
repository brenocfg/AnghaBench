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
struct microcode {scalar_t__ num_cores; scalar_t__ group; void* core_mask; int /*<<< orphan*/  version; scalar_t__ is_ae; } ;
struct device {int dummy; } ;
struct cpt_device {scalar_t__ max_ae_cores; scalar_t__ next_group; scalar_t__ max_se_cores; int /*<<< orphan*/  flags; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_TYPES ; 
 int /*<<< orphan*/  CPT_FLAG_DEVICE_READY ; 
 scalar_t__ CPT_MAX_CORE_GROUPS ; 
 int EINVAL ; 
 int ENFILE ; 
 void* GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_TYPES ; 
 int /*<<< orphan*/  cpt_configure_group (struct cpt_device*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_disable_all_interrupts (struct cpt_device*) ; 
 int /*<<< orphan*/  cpt_disable_cores (struct cpt_device*,void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cpt_enable_cores (struct cpt_device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_enable_mbox_interrupts (struct cpt_device*) ; 
 int cpt_load_microcode (struct cpt_device*,struct microcode*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 

__attribute__((used)) static int do_cpt_init(struct cpt_device *cpt, struct microcode *mcode)
{
	int ret = 0;
	struct device *dev = &cpt->pdev->dev;

	/* Make device not ready */
	cpt->flags &= ~CPT_FLAG_DEVICE_READY;
	/* Disable All PF interrupts */
	cpt_disable_all_interrupts(cpt);
	/* Calculate mcode group and coremasks */
	if (mcode->is_ae) {
		if (mcode->num_cores > cpt->max_ae_cores) {
			dev_err(dev, "Requested for more cores than available AE cores\n");
			ret = -EINVAL;
			goto cpt_init_fail;
		}

		if (cpt->next_group >= CPT_MAX_CORE_GROUPS) {
			dev_err(dev, "Can't load, all eight microcode groups in use");
			return -ENFILE;
		}

		mcode->group = cpt->next_group;
		/* Convert requested cores to mask */
		mcode->core_mask = GENMASK(mcode->num_cores, 0);
		cpt_disable_cores(cpt, mcode->core_mask, AE_TYPES,
				  mcode->group);
		/* Load microcode for AE engines */
		ret = cpt_load_microcode(cpt, mcode);
		if (ret) {
			dev_err(dev, "Microcode load Failed for %s\n",
				mcode->version);
			goto cpt_init_fail;
		}
		cpt->next_group++;
		/* Configure group mask for the mcode */
		cpt_configure_group(cpt, mcode->group, mcode->core_mask,
				    AE_TYPES);
		/* Enable AE cores for the group mask */
		cpt_enable_cores(cpt, mcode->core_mask, AE_TYPES);
	} else {
		if (mcode->num_cores > cpt->max_se_cores) {
			dev_err(dev, "Requested for more cores than available SE cores\n");
			ret = -EINVAL;
			goto cpt_init_fail;
		}
		if (cpt->next_group >= CPT_MAX_CORE_GROUPS) {
			dev_err(dev, "Can't load, all eight microcode groups in use");
			return -ENFILE;
		}

		mcode->group = cpt->next_group;
		/* Covert requested cores to mask */
		mcode->core_mask = GENMASK(mcode->num_cores, 0);
		cpt_disable_cores(cpt, mcode->core_mask, SE_TYPES,
				  mcode->group);
		/* Load microcode for SE engines */
		ret = cpt_load_microcode(cpt, mcode);
		if (ret) {
			dev_err(dev, "Microcode load Failed for %s\n",
				mcode->version);
			goto cpt_init_fail;
		}
		cpt->next_group++;
		/* Configure group mask for the mcode */
		cpt_configure_group(cpt, mcode->group, mcode->core_mask,
				    SE_TYPES);
		/* Enable SE cores for the group mask */
		cpt_enable_cores(cpt, mcode->core_mask, SE_TYPES);
	}

	/* Enabled PF mailbox interrupts */
	cpt_enable_mbox_interrupts(cpt);
	cpt->flags |= CPT_FLAG_DEVICE_READY;

	return ret;

cpt_init_fail:
	/* Enabled PF mailbox interrupts */
	cpt_enable_mbox_interrupts(cpt);

	return ret;
}