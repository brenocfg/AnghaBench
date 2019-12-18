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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  trans ;
struct pfr_buffer {scalar_t__ pfrb_caddr; scalar_t__ pfrb_size; } ;
struct pfioc_trans_e {int dummy; } ;
struct pfioc_trans {int esize; struct pfioc_trans_e* array; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct pfioc_trans*,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct pfioc_trans*) ; 

int
pfctl_trans(int dev, struct pfr_buffer *buf, u_long cmd, int from)
{
	struct pfioc_trans trans;

	bzero(&trans, sizeof(trans));
	trans.size = buf->pfrb_size - from;
	trans.esize = sizeof(struct pfioc_trans_e);
	trans.array = ((struct pfioc_trans_e *)buf->pfrb_caddr) + from;
	return ioctl(dev, cmd, &trans);
}