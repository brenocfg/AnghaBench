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
struct vop_read_args {int /*<<< orphan*/  a_vp; } ;
struct nfsnode {int /*<<< orphan*/  n_atim; int /*<<< orphan*/  n_flag; } ;
struct TYPE_2__ {int (* vop_read ) (struct vop_read_args*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NACC ; 
 int /*<<< orphan*/  NFSLOCKNODE (struct nfsnode*) ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (struct nfsnode*) ; 
 struct nfsnode* VTONFS (int /*<<< orphan*/ ) ; 
 TYPE_1__ fifo_specops ; 
 int stub1 (struct vop_read_args*) ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfsfifo_read(struct vop_read_args *ap)
{
	struct nfsnode *np = VTONFS(ap->a_vp);
	int error;

	/*
	 * Set access flag.
	 */
	NFSLOCKNODE(np);
	np->n_flag |= NACC;
	vfs_timestamp(&np->n_atim);
	NFSUNLOCKNODE(np);
	error = fifo_specops.vop_read(ap);
	return error;	
}