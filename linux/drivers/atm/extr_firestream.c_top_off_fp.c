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
typedef  int u32 ;
struct sk_buff {struct FS_BPENTRY* data; int /*<<< orphan*/  head; } ;
struct fs_dev {int dummy; } ;
struct freepool {scalar_t__ nr_buffers; int bufsize; int /*<<< orphan*/  offset; int /*<<< orphan*/  n; } ;
struct FS_BPENTRY {int flags; int next; int bsa; int aal_bufsize; struct freepool* fp; struct sk_buff* skb; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  FP_CNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_CTU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FP_EA (int /*<<< orphan*/ ) ; 
 int FP_FLAGS_EPI ; 
 int /*<<< orphan*/  FP_SA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_DEBUG_ALLOC ; 
 int /*<<< orphan*/  FS_DEBUG_QUEUE ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 struct FS_BPENTRY* bus_to_virt (long) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  fs_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 struct FS_BPENTRY* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nr_buffers_in_freepool (struct fs_dev*,struct freepool*) ; 
 int read_fs (struct fs_dev*,int /*<<< orphan*/ ) ; 
 int virt_to_bus (struct FS_BPENTRY*) ; 
 int /*<<< orphan*/  write_fs (struct fs_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void top_off_fp (struct fs_dev *dev, struct freepool *fp,
			gfp_t gfp_flags)
{
	struct FS_BPENTRY *qe, *ne;
	struct sk_buff *skb;
	int n = 0;
	u32 qe_tmp;

	fs_dprintk (FS_DEBUG_QUEUE, "Topping off queue at %x (%d-%d/%d)\n", 
		    fp->offset, read_fs (dev, FP_CNT (fp->offset)), fp->n, 
		    fp->nr_buffers);
	while (nr_buffers_in_freepool(dev, fp) < fp->nr_buffers) {

		skb = alloc_skb (fp->bufsize, gfp_flags);
		fs_dprintk (FS_DEBUG_ALLOC, "Alloc rec-skb: %p(%d)\n", skb, fp->bufsize);
		if (!skb) break;
		ne = kmalloc (sizeof (struct FS_BPENTRY), gfp_flags);
		fs_dprintk (FS_DEBUG_ALLOC, "Alloc rec-d: %p(%zd)\n", ne, sizeof (struct FS_BPENTRY));
		if (!ne) {
			fs_dprintk (FS_DEBUG_ALLOC, "Free rec-skb: %p\n", skb);
			dev_kfree_skb_any (skb);
			break;
		}

		fs_dprintk (FS_DEBUG_QUEUE, "Adding skb %p desc %p -> %p(%p) ", 
			    skb, ne, skb->data, skb->head);
		n++;
		ne->flags = FP_FLAGS_EPI | fp->bufsize;
		ne->next  = virt_to_bus (NULL);
		ne->bsa   = virt_to_bus (skb->data);
		ne->aal_bufsize = fp->bufsize;
		ne->skb = skb;
		ne->fp = fp;

		/*
		 * FIXME: following code encodes and decodes
		 * machine pointers (could be 64-bit) into a
		 * 32-bit register.
		 */

		qe_tmp = read_fs (dev, FP_EA(fp->offset));
		fs_dprintk (FS_DEBUG_QUEUE, "link at %x\n", qe_tmp);
		if (qe_tmp) {
			qe = bus_to_virt ((long) qe_tmp);
			qe->next = virt_to_bus(ne);
			qe->flags &= ~FP_FLAGS_EPI;
		} else
			write_fs (dev, FP_SA(fp->offset), virt_to_bus(ne));

		write_fs (dev, FP_EA(fp->offset), virt_to_bus (ne));
		fp->n++;   /* XXX Atomic_inc? */
		write_fs (dev, FP_CTU(fp->offset), 1);
	}

	fs_dprintk (FS_DEBUG_QUEUE, "Added %d entries. \n", n);
}