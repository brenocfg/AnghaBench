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
struct vc_map {int lacr; int index; int /*<<< orphan*/  flags; } ;
struct idt77252_dev {int /*<<< orphan*/  mutex; } ;
struct atm_vcc {int /*<<< orphan*/  flags; int /*<<< orphan*/  qos; struct vc_map* dev_data; struct atm_dev* dev; } ;
struct TYPE_4__ {scalar_t__ traffic_class; } ;
struct TYPE_3__ {scalar_t__ traffic_class; } ;
struct atm_qos {TYPE_2__ rxtp; TYPE_1__ txtp; } ;
struct atm_dev {struct idt77252_dev* dev_data; } ;

/* Variables and functions */
#define  ATM_ABR 131 
#define  ATM_CBR 130 
 scalar_t__ ATM_NONE ; 
#define  ATM_UBR 129 
#define  ATM_VBR 128 
 int /*<<< orphan*/  ATM_VF_HASQOS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SAR_REG_TCMDQ ; 
 int TCMDQ_LACR ; 
 int /*<<< orphan*/  VCF_IDLE ; 
 int /*<<< orphan*/  VCF_RX ; 
 int /*<<< orphan*/  VCF_TX ; 
 int idt77252_init_cbr (struct idt77252_dev*,struct vc_map*,struct atm_vcc*,struct atm_qos*) ; 
 int idt77252_init_rx (struct idt77252_dev*,struct vc_map*,struct atm_vcc*,struct atm_qos*) ; 
 int idt77252_init_tx (struct idt77252_dev*,struct vc_map*,struct atm_vcc*,struct atm_qos*) ; 
 int idt77252_init_ubr (struct idt77252_dev*,struct vc_map*,struct atm_vcc*,struct atm_qos*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct atm_qos*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idt77252_change_qos(struct atm_vcc *vcc, struct atm_qos *qos, int flags)
{
	struct atm_dev *dev = vcc->dev;
	struct idt77252_dev *card = dev->dev_data;
	struct vc_map *vc = vcc->dev_data;
	int error = 0;

	mutex_lock(&card->mutex);

	if (qos->txtp.traffic_class != ATM_NONE) {
	    	if (!test_bit(VCF_TX, &vc->flags)) {
			error = idt77252_init_tx(card, vc, vcc, qos);
			if (error)
				goto out;
		} else {
			switch (qos->txtp.traffic_class) {
			case ATM_CBR:
				error = idt77252_init_cbr(card, vc, vcc, qos);
				if (error)
					goto out;
				break;

			case ATM_UBR:
				error = idt77252_init_ubr(card, vc, vcc, qos);
				if (error)
					goto out;

				if (!test_bit(VCF_IDLE, &vc->flags)) {
					writel(TCMDQ_LACR | (vc->lacr << 16) |
					       vc->index, SAR_REG_TCMDQ);
				}
				break;

			case ATM_VBR:
			case ATM_ABR:
				error = -EOPNOTSUPP;
				goto out;
			}
		}
	}

	if ((qos->rxtp.traffic_class != ATM_NONE) &&
	    !test_bit(VCF_RX, &vc->flags)) {
		error = idt77252_init_rx(card, vc, vcc, qos);
		if (error)
			goto out;
	}

	memcpy(&vcc->qos, qos, sizeof(struct atm_qos));

	set_bit(ATM_VF_HASQOS, &vcc->flags);

out:
	mutex_unlock(&card->mutex);
	return error;
}