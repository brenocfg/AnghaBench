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
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  phase; } ;
struct pp_struct {int /*<<< orphan*/ * pdev; int /*<<< orphan*/  irq_wait; int /*<<< orphan*/  irqc; scalar_t__ irqresponse; scalar_t__ flags; TYPE_1__ state; } ;
struct inode {int dummy; } ;
struct file {struct pp_struct* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE1284_MODE_COMPAT ; 
 unsigned int PARPORT_MAX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  init_phase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct pp_struct* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pp_open(struct inode *inode, struct file *file)
{
	unsigned int minor = iminor(inode);
	struct pp_struct *pp;

	if (minor >= PARPORT_MAX)
		return -ENXIO;

	pp = kmalloc(sizeof(struct pp_struct), GFP_KERNEL);
	if (!pp)
		return -ENOMEM;

	pp->state.mode = IEEE1284_MODE_COMPAT;
	pp->state.phase = init_phase(pp->state.mode);
	pp->flags = 0;
	pp->irqresponse = 0;
	atomic_set(&pp->irqc, 0);
	init_waitqueue_head(&pp->irq_wait);

	/* Defer the actual device registration until the first claim.
	 * That way, we know whether or not the driver wants to have
	 * exclusive access to the port (PPEXCL).
	 */
	pp->pdev = NULL;
	file->private_data = pp;

	return 0;
}