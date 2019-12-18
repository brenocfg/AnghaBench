#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_10__ {TYPE_3__* rxq; TYPE_2__ txq; TYPE_1__ cq; int /*<<< orphan*/  vcc_sf; void* rx_avail; void* tx_avail; scalar_t__ flags; int /*<<< orphan*/  membase; int /*<<< orphan*/  irq; int /*<<< orphan*/  iobase; struct pci_dev* pci_dev; } ;
typedef  TYPE_4__ amb_dev ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 void* ATM_OC3_PCR ; 
 unsigned char NUM_RX_POOLS ; 
 int /*<<< orphan*/  bus_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,TYPE_4__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_dev(amb_dev *dev, struct pci_dev *pci_dev) 
{
      unsigned char pool;
      
      // set up known dev items straight away
      dev->pci_dev = pci_dev; 
      pci_set_drvdata(pci_dev, dev);
      
      dev->iobase = pci_resource_start (pci_dev, 1);
      dev->irq = pci_dev->irq; 
      dev->membase = bus_to_virt(pci_resource_start(pci_dev, 0));
      
      // flags (currently only dead)
      dev->flags = 0;
      
      // Allocate cell rates (fibre)
      // ATM_OC3_PCR = 1555200000/8/270*260/53 - 29/53
      // to be really pedantic, this should be ATM_OC3c_PCR
      dev->tx_avail = ATM_OC3_PCR;
      dev->rx_avail = ATM_OC3_PCR;
      
      // semaphore for txer/rxer modifications - we cannot use a
      // spinlock as the critical region needs to switch processes
      mutex_init(&dev->vcc_sf);
      // queue manipulation spinlocks; we want atomic reads and
      // writes to the queue descriptors (handles IRQ and SMP)
      // consider replacing "int pending" -> "atomic_t available"
      // => problem related to who gets to move queue pointers
      spin_lock_init (&dev->cq.lock);
      spin_lock_init (&dev->txq.lock);
      for (pool = 0; pool < NUM_RX_POOLS; ++pool)
	spin_lock_init (&dev->rxq[pool].lock);
}