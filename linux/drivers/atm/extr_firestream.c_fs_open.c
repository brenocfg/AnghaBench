#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fs_vcc {short channo; int flags; short atm_hdr; unsigned short* TMC; scalar_t__* rtag; scalar_t__ spec; int /*<<< orphan*/  close_wait; int /*<<< orphan*/ * last_skb; } ;
struct fs_transmit_config {short channo; int flags; short atm_hdr; unsigned short* TMC; scalar_t__* rtag; scalar_t__ spec; int /*<<< orphan*/  close_wait; int /*<<< orphan*/ * last_skb; } ;
struct fs_dev {int channo; short channel_mask; int /*<<< orphan*/  hp_txq; struct atm_vcc** atm_vccs; TYPE_1__* rx_fp; int /*<<< orphan*/ * tx_inuse; } ;
struct atm_trafprm {scalar_t__ max_sdu; } ;
struct TYPE_5__ {int aal; struct atm_trafprm rxtp; struct atm_trafprm txtp; } ;
struct atm_vcc {short vpi; int vci; int /*<<< orphan*/  flags; TYPE_2__ qos; struct fs_vcc* dev_data; TYPE_3__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  number; } ;
struct TYPE_4__ {scalar_t__ bufsize; } ;

/* Variables and functions */
#define  ATM_AAL0 130 
#define  ATM_AAL2 129 
#define  ATM_AAL5 128 
 short ATM_VCI_UNSPEC ; 
 int ATM_VF_ADDR ; 
 size_t ATM_VF_PARTIAL ; 
 int ATM_VF_READY ; 
 int ATM_VPI_UNSPEC ; 
 scalar_t__ DO_DIRECTION (struct atm_trafprm*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 short FS155_VCI_BITS ; 
 int /*<<< orphan*/  FS_DEBUG_ALLOC ; 
 int FS_DEBUG_OPEN ; 
 struct fs_dev* FS_DEV (TYPE_3__*) ; 
 int FS_NR_FREE_POOLS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_FS50 (struct fs_dev*) ; 
 int QE_CMD_CONFIG_RX ; 
 int QE_CMD_CONFIG_TX ; 
 int QE_CMD_IMM_INQ ; 
 int QE_CMD_REG_WR ; 
 int QE_CMD_RX_EN ; 
 int QE_CMD_TX_EN ; 
 int RC_FLAGS_AAL5 ; 
 int RC_FLAGS_BFPS_BFP ; 
 int RC_FLAGS_RXBM_PSB ; 
 int RC_FLAGS_TRANSP ; 
 int ROUND_DOWN ; 
 int ROUND_UP ; 
 int TC_FLAGS_AAL5 ; 
 int TC_FLAGS_CAL0 ; 
 int TC_FLAGS_PACKET ; 
 int TC_FLAGS_TRANSPARENT_PAYLOAD ; 
 int TC_FLAGS_TYPE_CBR ; 
 int TC_FLAGS_TYPE_UBR ; 
 int atm_pcr_goal (struct atm_trafprm*) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int fs_debug ; 
 int /*<<< orphan*/  fs_dprintk (int,char*,...) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fs_vcc*) ; 
 struct fs_vcc* kmalloc (int,int /*<<< orphan*/ ) ; 
 int make_rate (int,int,unsigned short*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  my_hd (struct fs_vcc*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_command (struct fs_dev*,int /*<<< orphan*/ *,int,int,short,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ *) ; 
 int virt_to_bus (struct fs_vcc*) ; 

__attribute__((used)) static int fs_open(struct atm_vcc *atm_vcc)
{
	struct fs_dev *dev;
	struct fs_vcc *vcc;
	struct fs_transmit_config *tc;
	struct atm_trafprm * txtp;
	struct atm_trafprm * rxtp;
	/*  struct fs_receive_config *rc;*/
	/*  struct FS_QENTRY *qe; */
	int error;
	int bfp;
	int to;
	unsigned short tmc0;
	short vpi = atm_vcc->vpi;
	int vci = atm_vcc->vci;

	func_enter ();

	dev = FS_DEV(atm_vcc->dev);
	fs_dprintk (FS_DEBUG_OPEN, "fs: open on dev: %p, vcc at %p\n", 
		    dev, atm_vcc);

	if (vci != ATM_VPI_UNSPEC && vpi != ATM_VCI_UNSPEC)
		set_bit(ATM_VF_ADDR, &atm_vcc->flags);

	if ((atm_vcc->qos.aal != ATM_AAL5) &&
	    (atm_vcc->qos.aal != ATM_AAL2))
	  return -EINVAL; /* XXX AAL0 */

	fs_dprintk (FS_DEBUG_OPEN, "fs: (itf %d): open %d.%d\n", 
		    atm_vcc->dev->number, atm_vcc->vpi, atm_vcc->vci);	

	/* XXX handle qos parameters (rate limiting) ? */

	vcc = kmalloc(sizeof(struct fs_vcc), GFP_KERNEL);
	fs_dprintk (FS_DEBUG_ALLOC, "Alloc VCC: %p(%zd)\n", vcc, sizeof(struct fs_vcc));
	if (!vcc) {
		clear_bit(ATM_VF_ADDR, &atm_vcc->flags);
		return -ENOMEM;
	}
  
	atm_vcc->dev_data = vcc;
	vcc->last_skb = NULL;

	init_waitqueue_head (&vcc->close_wait);

	txtp = &atm_vcc->qos.txtp;
	rxtp = &atm_vcc->qos.rxtp;

	if (!test_bit(ATM_VF_PARTIAL, &atm_vcc->flags)) {
		if (IS_FS50(dev)) {
			/* Increment the channel numer: take a free one next time.  */
			for (to=33;to;to--, dev->channo++) {
				/* We only have 32 channels */
				if (dev->channo >= 32)
					dev->channo = 0;
				/* If we need to do RX, AND the RX is inuse, try the next */
				if (DO_DIRECTION(rxtp) && dev->atm_vccs[dev->channo])
					continue;
				/* If we need to do TX, AND the TX is inuse, try the next */
				if (DO_DIRECTION(txtp) && test_bit (dev->channo, dev->tx_inuse))
					continue;
				/* Ok, both are free! (or not needed) */
				break;
			}
			if (!to) {
				printk ("No more free channels for FS50..\n");
				return -EBUSY;
			}
			vcc->channo = dev->channo;
			dev->channo &= dev->channel_mask;
      
		} else {
			vcc->channo = (vpi << FS155_VCI_BITS) | (vci);
			if (((DO_DIRECTION(rxtp) && dev->atm_vccs[vcc->channo])) ||
			    ( DO_DIRECTION(txtp) && test_bit (vcc->channo, dev->tx_inuse))) {
				printk ("Channel is in use for FS155.\n");
				return -EBUSY;
			}
		}
		fs_dprintk (FS_DEBUG_OPEN, "OK. Allocated channel %x(%d).\n", 
			    vcc->channo, vcc->channo);
	}

	if (DO_DIRECTION (txtp)) {
		tc = kmalloc (sizeof (struct fs_transmit_config), GFP_KERNEL);
		fs_dprintk (FS_DEBUG_ALLOC, "Alloc tc: %p(%zd)\n",
			    tc, sizeof (struct fs_transmit_config));
		if (!tc) {
			fs_dprintk (FS_DEBUG_OPEN, "fs: can't alloc transmit_config.\n");
			return -ENOMEM;
		}

		/* Allocate the "open" entry from the high priority txq. This makes
		   it most likely that the chip will notice it. It also prevents us
		   from having to wait for completion. On the other hand, we may
		   need to wait for completion anyway, to see if it completed
		   successfully. */

		switch (atm_vcc->qos.aal) {
		case ATM_AAL2:
		case ATM_AAL0:
		  tc->flags = 0
		    | TC_FLAGS_TRANSPARENT_PAYLOAD
		    | TC_FLAGS_PACKET
		    | (1 << 28)
		    | TC_FLAGS_TYPE_UBR /* XXX Change to VBR -- PVDL */
		    | TC_FLAGS_CAL0;
		  break;
		case ATM_AAL5:
		  tc->flags = 0
			| TC_FLAGS_AAL5
			| TC_FLAGS_PACKET  /* ??? */
			| TC_FLAGS_TYPE_CBR
			| TC_FLAGS_CAL0;
		  break;
		default:
			printk ("Unknown aal: %d\n", atm_vcc->qos.aal);
			tc->flags = 0;
		}
		/* Docs are vague about this atm_hdr field. By the way, the FS
		 * chip makes odd errors if lower bits are set.... -- REW */
		tc->atm_hdr =  (vpi << 20) | (vci << 4); 
		tmc0 = 0;
		{
			int pcr = atm_pcr_goal (txtp);

			fs_dprintk (FS_DEBUG_OPEN, "pcr = %d.\n", pcr);

			/* XXX Hmm. officially we're only allowed to do this if rounding 
			   is round_down -- REW */
			if (IS_FS50(dev)) {
				if (pcr > 51840000/53/8)  pcr = 51840000/53/8;
			} else {
				if (pcr > 155520000/53/8) pcr = 155520000/53/8;
			}
			if (!pcr) {
				/* no rate cap */
				tmc0 = IS_FS50(dev)?0x61BE:0x64c9; /* Just copied over the bits from Fujitsu -- REW */
			} else {
				int r;
				if (pcr < 0) {
					r = ROUND_DOWN;
					pcr = -pcr;
				} else {
					r = ROUND_UP;
				}
				error = make_rate (pcr, r, &tmc0, NULL);
				if (error) {
					kfree(tc);
					return error;
				}
			}
			fs_dprintk (FS_DEBUG_OPEN, "pcr = %d.\n", pcr);
		}
      
		tc->TMC[0] = tmc0 | 0x4000;
		tc->TMC[1] = 0; /* Unused */
		tc->TMC[2] = 0; /* Unused */
		tc->TMC[3] = 0; /* Unused */
    
		tc->spec = 0;    /* UTOPIA address, UDF, HEC: Unused -> 0 */
		tc->rtag[0] = 0; /* What should I do with routing tags??? 
				    -- Not used -- AS -- Thanks -- REW*/
		tc->rtag[1] = 0;
		tc->rtag[2] = 0;

		if (fs_debug & FS_DEBUG_OPEN) {
			fs_dprintk (FS_DEBUG_OPEN, "TX config record:\n");
			my_hd (tc, sizeof (*tc));
		}

		/* We now use the "submit_command" function to submit commands to
		   the firestream. There is a define up near the definition of
		   that routine that switches this routine between immediate write
		   to the immediate command registers and queuing the commands in
		   the HPTXQ for execution. This last technique might be more
		   efficient if we know we're going to submit a whole lot of
		   commands in one go, but this driver is not setup to be able to
		   use such a construct. So it probably doen't matter much right
		   now. -- REW */
    
		/* The command is IMMediate and INQueue. The parameters are out-of-line.. */
		submit_command (dev, &dev->hp_txq, 
				QE_CMD_CONFIG_TX | QE_CMD_IMM_INQ | vcc->channo,
				virt_to_bus (tc), 0, 0);

		submit_command (dev, &dev->hp_txq, 
				QE_CMD_TX_EN | QE_CMD_IMM_INQ | vcc->channo,
				0, 0, 0);
		set_bit (vcc->channo, dev->tx_inuse);
	}

	if (DO_DIRECTION (rxtp)) {
		dev->atm_vccs[vcc->channo] = atm_vcc;

		for (bfp = 0;bfp < FS_NR_FREE_POOLS; bfp++)
			if (atm_vcc->qos.rxtp.max_sdu <= dev->rx_fp[bfp].bufsize) break;
		if (bfp >= FS_NR_FREE_POOLS) {
			fs_dprintk (FS_DEBUG_OPEN, "No free pool fits sdu: %d.\n", 
				    atm_vcc->qos.rxtp.max_sdu);
			/* XXX Cleanup? -- Would just calling fs_close work??? -- REW */

			/* XXX clear tx inuse. Close TX part? */
			dev->atm_vccs[vcc->channo] = NULL;
			kfree (vcc);
			return -EINVAL;
		}

		switch (atm_vcc->qos.aal) {
		case ATM_AAL0:
		case ATM_AAL2:
			submit_command (dev, &dev->hp_txq,
					QE_CMD_CONFIG_RX | QE_CMD_IMM_INQ | vcc->channo,
					RC_FLAGS_TRANSP |
					RC_FLAGS_BFPS_BFP * bfp |
					RC_FLAGS_RXBM_PSB, 0, 0);
			break;
		case ATM_AAL5:
			submit_command (dev, &dev->hp_txq,
					QE_CMD_CONFIG_RX | QE_CMD_IMM_INQ | vcc->channo,
					RC_FLAGS_AAL5 |
					RC_FLAGS_BFPS_BFP * bfp |
					RC_FLAGS_RXBM_PSB, 0, 0);
			break;
		};
		if (IS_FS50 (dev)) {
			submit_command (dev, &dev->hp_txq, 
					QE_CMD_REG_WR | QE_CMD_IMM_INQ,
					0x80 + vcc->channo,
					(vpi << 16) | vci, 0 ); /* XXX -- Use defines. */
		}
		submit_command (dev, &dev->hp_txq, 
				QE_CMD_RX_EN | QE_CMD_IMM_INQ | vcc->channo,
				0, 0, 0);
	}
    
	/* Indicate we're done! */
	set_bit(ATM_VF_READY, &atm_vcc->flags);

	func_exit ();
	return 0;
}