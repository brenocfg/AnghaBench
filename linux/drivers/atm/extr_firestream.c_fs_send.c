#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int len; struct FS_BPENTRY* data; } ;
struct fs_vcc {int channo; struct sk_buff* last_skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct fs_dev {TYPE_1__ tx_relq; TYPE_2__ hp_txq; int /*<<< orphan*/  ntxpckts; } ;
struct atm_vcc {int /*<<< orphan*/  dev; } ;
struct FS_BPENTRY {int flags; struct fs_dev* dev; struct sk_buff* skb; int /*<<< orphan*/  bsa; scalar_t__ next; } ;
struct TYPE_8__ {struct atm_vcc* vcc; } ;
struct TYPE_7__ {int flags; struct fs_dev* dev; struct sk_buff* skb; int /*<<< orphan*/  bsa; scalar_t__ next; } ;

/* Variables and functions */
 TYPE_4__* ATM_SKB (struct sk_buff*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FS_DEBUG_ALLOC ; 
 int /*<<< orphan*/  FS_DEBUG_QUEUE ; 
 int /*<<< orphan*/  FS_DEBUG_SEND ; 
 int /*<<< orphan*/  FS_DEBUG_TXMEM ; 
 struct fs_dev* FS_DEV (int /*<<< orphan*/ ) ; 
 struct fs_vcc* FS_VCC (struct atm_vcc*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int QE_TRANSMIT_DE ; 
 int /*<<< orphan*/  Q_EA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_SA (int /*<<< orphan*/ ) ; 
 int TD_DATA ; 
 int TD_EPI ; 
 struct FS_BPENTRY** da ; 
 TYPE_3__* dq ; 
 int /*<<< orphan*/  fs_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 struct FS_BPENTRY* kmalloc (int,int /*<<< orphan*/ ) ; 
 size_t qd ; 
 int /*<<< orphan*/  read_fs (struct fs_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_queue (struct fs_dev*,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_bus (struct FS_BPENTRY*) ; 

__attribute__((used)) static int fs_send (struct atm_vcc *atm_vcc, struct sk_buff *skb)
{
	struct fs_dev *dev = FS_DEV (atm_vcc->dev);
	struct fs_vcc *vcc = FS_VCC (atm_vcc);
	struct FS_BPENTRY *td;

	func_enter ();

	fs_dprintk (FS_DEBUG_TXMEM, "I");
	fs_dprintk (FS_DEBUG_SEND, "Send: atm_vcc %p skb %p vcc %p dev %p\n", 
		    atm_vcc, skb, vcc, dev);

	fs_dprintk (FS_DEBUG_ALLOC, "Alloc t-skb: %p (atm_send)\n", skb);

	ATM_SKB(skb)->vcc = atm_vcc;

	vcc->last_skb = skb;

	td = kmalloc (sizeof (struct FS_BPENTRY), GFP_ATOMIC);
	fs_dprintk (FS_DEBUG_ALLOC, "Alloc transd: %p(%zd)\n", td, sizeof (struct FS_BPENTRY));
	if (!td) {
		/* Oops out of mem */
		return -ENOMEM;
	}

	fs_dprintk (FS_DEBUG_SEND, "first word in buffer: %x\n", 
		    *(int *) skb->data);

	td->flags =  TD_EPI | TD_DATA | skb->len;
	td->next = 0;
	td->bsa  = virt_to_bus (skb->data);
	td->skb = skb;
	td->dev = dev;
	dev->ntxpckts++;

#ifdef DEBUG_EXTRA
	da[qd] = td;
	dq[qd].flags = td->flags;
	dq[qd].next  = td->next;
	dq[qd].bsa   = td->bsa;
	dq[qd].skb   = td->skb;
	dq[qd].dev   = td->dev;
	qd++;
	if (qd >= 60) qd = 0;
#endif

	submit_queue (dev, &dev->hp_txq, 
		      QE_TRANSMIT_DE | vcc->channo,
		      virt_to_bus (td), 0, 
		      virt_to_bus (td));

	fs_dprintk (FS_DEBUG_QUEUE, "in send: txq %d txrq %d\n", 
		    read_fs (dev, Q_EA (dev->hp_txq.offset)) -
		    read_fs (dev, Q_SA (dev->hp_txq.offset)),
		    read_fs (dev, Q_EA (dev->tx_relq.offset)) -
		    read_fs (dev, Q_SA (dev->tx_relq.offset)));

	func_exit ();
	return 0;
}