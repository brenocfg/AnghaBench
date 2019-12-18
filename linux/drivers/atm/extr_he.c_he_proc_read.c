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
struct he_tpdrq {int dummy; } ;
struct he_rbrq {int dummy; } ;
struct he_rbp {int dummy; } ;
struct he_dev {char* prod_id; int media; int irq_peak; int rbrq_peak; int tbrq_peak; int total_bw; TYPE_2__* atm_dev; TYPE_1__* cs_stper; int /*<<< orphan*/  global_lock; } ;
struct atm_dev {int dummy; } ;
typedef  int loff_t ;
struct TYPE_4__ {int link_rate; } ;
struct TYPE_3__ {int /*<<< orphan*/  inuse; int /*<<< orphan*/  pcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEC ; 
 int CONFIG_IRQ_SIZE ; 
 int CONFIG_RBPL_SIZE ; 
 int CONFIG_RBRQ_SIZE ; 
 int CONFIG_TBRQ_SIZE ; 
 int CONFIG_TPDRQ_SIZE ; 
 int /*<<< orphan*/  DCC ; 
 int /*<<< orphan*/  G0_RBPL_S ; 
 int /*<<< orphan*/  G0_RBPL_T ; 
 struct he_dev* HE_DEV (struct atm_dev*) ; 
 int HE_NUM_CS_STPER ; 
 int /*<<< orphan*/  MCC ; 
 int /*<<< orphan*/  OEC ; 
 int RBPL_MASK (scalar_t__) ; 
 scalar_t__ he_readl (struct he_dev*,int /*<<< orphan*/ ) ; 
 int inuse ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int
he_proc_read(struct atm_dev *dev, loff_t *pos, char *page)
{
	unsigned long flags;
	struct he_dev *he_dev = HE_DEV(dev);
	int left, i;
#ifdef notdef
	struct he_rbrq *rbrq_tail;
	struct he_tpdrq *tpdrq_head;
	int rbpl_head, rbpl_tail;
#endif
	static long mcc = 0, oec = 0, dcc = 0, cec = 0;


	left = *pos;
	if (!left--)
		return sprintf(page, "ATM he driver\n");

	if (!left--)
		return sprintf(page, "%s%s\n\n",
			he_dev->prod_id, he_dev->media & 0x40 ? "SM" : "MM");

	if (!left--)
		return sprintf(page, "Mismatched Cells  VPI/VCI Not Open  Dropped Cells  RCM Dropped Cells\n");

	spin_lock_irqsave(&he_dev->global_lock, flags);
	mcc += he_readl(he_dev, MCC);
	oec += he_readl(he_dev, OEC);
	dcc += he_readl(he_dev, DCC);
	cec += he_readl(he_dev, CEC);
	spin_unlock_irqrestore(&he_dev->global_lock, flags);

	if (!left--)
		return sprintf(page, "%16ld  %16ld  %13ld  %17ld\n\n", 
							mcc, oec, dcc, cec);

	if (!left--)
		return sprintf(page, "irq_size = %d  inuse = ?  peak = %d\n",
				CONFIG_IRQ_SIZE, he_dev->irq_peak);

	if (!left--)
		return sprintf(page, "tpdrq_size = %d  inuse = ?\n",
						CONFIG_TPDRQ_SIZE);

	if (!left--)
		return sprintf(page, "rbrq_size = %d  inuse = ?  peak = %d\n",
				CONFIG_RBRQ_SIZE, he_dev->rbrq_peak);

	if (!left--)
		return sprintf(page, "tbrq_size = %d  peak = %d\n",
					CONFIG_TBRQ_SIZE, he_dev->tbrq_peak);


#ifdef notdef
	rbpl_head = RBPL_MASK(he_readl(he_dev, G0_RBPL_S));
	rbpl_tail = RBPL_MASK(he_readl(he_dev, G0_RBPL_T));

	inuse = rbpl_head - rbpl_tail;
	if (inuse < 0)
		inuse += CONFIG_RBPL_SIZE * sizeof(struct he_rbp);
	inuse /= sizeof(struct he_rbp);

	if (!left--)
		return sprintf(page, "rbpl_size = %d  inuse = %d\n\n",
						CONFIG_RBPL_SIZE, inuse);
#endif

	if (!left--)
		return sprintf(page, "rate controller periods (cbr)\n                 pcr  #vc\n");

	for (i = 0; i < HE_NUM_CS_STPER; ++i)
		if (!left--)
			return sprintf(page, "cs_stper%-2d  %8ld  %3d\n", i,
						he_dev->cs_stper[i].pcr,
						he_dev->cs_stper[i].inuse);

	if (!left--)
		return sprintf(page, "total bw (cbr): %d  (limit %d)\n",
			he_dev->total_bw, he_dev->atm_dev->link_rate * 10 / 9);

	return 0;
}