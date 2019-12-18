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
struct queue {int /*<<< orphan*/  sa; int /*<<< orphan*/  offset; } ;
struct fs_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_DEBUG_ALLOC ; 
 int /*<<< orphan*/  Q_EA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_RP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_SA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_WP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fs (struct fs_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_queue(struct fs_dev *dev, struct queue *txq)
{
	func_enter ();

	write_fs (dev, Q_SA(txq->offset), 0);
	write_fs (dev, Q_EA(txq->offset), 0);
	write_fs (dev, Q_RP(txq->offset), 0);
	write_fs (dev, Q_WP(txq->offset), 0);
	/* Configuration ? */

	fs_dprintk (FS_DEBUG_ALLOC, "Free queue: %p\n", txq->sa);
	kfree (txq->sa);

	func_exit ();
}