#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct queue {int offset; struct FS_QENTRY* ea; struct FS_QENTRY* sa; } ;
struct fs_dev {int dummy; } ;
struct FS_QENTRY {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_DEBUG_ALLOC ; 
 int /*<<< orphan*/  FS_DEBUG_INIT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  Q_CNF (int) ; 
 int /*<<< orphan*/  Q_EA (int) ; 
 int /*<<< orphan*/  Q_RP (int) ; 
 int /*<<< orphan*/  Q_SA (int) ; 
 int /*<<< orphan*/  Q_WP (int) ; 
 struct FS_QENTRY* aligned_kmalloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fs_dprintk (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  virt_to_bus (struct FS_QENTRY*) ; 
 int /*<<< orphan*/  write_fs (struct fs_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_q(struct fs_dev *dev, struct queue *txq, int queue,
		  int nentries, int is_rq)
{
	int sz = nentries * sizeof (struct FS_QENTRY);
	struct FS_QENTRY *p;

	func_enter ();

	fs_dprintk (FS_DEBUG_INIT, "Initializing queue at %x: %d entries:\n",
		    queue, nentries);

	p = aligned_kmalloc (sz, GFP_KERNEL, 0x10);
	fs_dprintk (FS_DEBUG_ALLOC, "Alloc queue: %p(%d)\n", p, sz);

	if (!p) return 0;

	write_fs (dev, Q_SA(queue), virt_to_bus(p));
	write_fs (dev, Q_EA(queue), virt_to_bus(p+nentries-1));
	write_fs (dev, Q_WP(queue), virt_to_bus(p));
	write_fs (dev, Q_RP(queue), virt_to_bus(p));
	if (is_rq) {
		/* Configuration for the receive queue: 0: interrupt immediately,
		   no pre-warning to empty queues: We do our best to keep the
		   queue filled anyway. */
		write_fs (dev, Q_CNF(queue), 0 ); 
	}

	txq->sa = p;
	txq->ea = p;
	txq->offset = queue; 

	func_exit ();
	return 1;
}