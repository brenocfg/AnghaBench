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
struct scatterlist {unsigned int offset; unsigned int length; } ;
struct page {int dummy; } ;
struct TYPE_5__ {int flags; } ;
struct ata_queued_cmd {unsigned int curbytes; unsigned int cursg_ofs; struct scatterlist* cursg; TYPE_2__ tf; int /*<<< orphan*/  nbytes; struct ata_device* dev; struct ata_port* ap; } ;
struct ata_port {TYPE_3__* ops; } ;
struct ata_eh_info {int dummy; } ;
struct ata_device {TYPE_1__* link; } ;
struct TYPE_6__ {unsigned int (* sff_data_xfer ) (struct ata_queued_cmd*,unsigned char*,unsigned int,int) ;} ;
struct TYPE_4__ {struct ata_eh_info eh_info; } ;

/* Variables and functions */
 int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  DPRINTK (char*,char*) ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int READ ; 
 int WRITE ; 
 int /*<<< orphan*/  ata_ehi_push_desc (struct ata_eh_info*,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned char*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct page* nth_page (struct page*,unsigned int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 struct page* sg_page (struct scatterlist*) ; 
 unsigned int stub1 (struct ata_queued_cmd*,unsigned char*,unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __atapi_pio_bytes(struct ata_queued_cmd *qc, unsigned int bytes)
{
	int rw = (qc->tf.flags & ATA_TFLAG_WRITE) ? WRITE : READ;
	struct ata_port *ap = qc->ap;
	struct ata_device *dev = qc->dev;
	struct ata_eh_info *ehi = &dev->link->eh_info;
	struct scatterlist *sg;
	struct page *page;
	unsigned char *buf;
	unsigned int offset, count, consumed;

next_sg:
	sg = qc->cursg;
	if (unlikely(!sg)) {
		ata_ehi_push_desc(ehi, "unexpected or too much trailing data "
				  "buf=%u cur=%u bytes=%u",
				  qc->nbytes, qc->curbytes, bytes);
		return -1;
	}

	page = sg_page(sg);
	offset = sg->offset + qc->cursg_ofs;

	/* get the current page and offset */
	page = nth_page(page, (offset >> PAGE_SHIFT));
	offset %= PAGE_SIZE;

	/* don't overrun current sg */
	count = min(sg->length - qc->cursg_ofs, bytes);

	/* don't cross page boundaries */
	count = min(count, (unsigned int)PAGE_SIZE - offset);

	DPRINTK("data %s\n", qc->tf.flags & ATA_TFLAG_WRITE ? "write" : "read");

	/* do the actual data transfer */
	buf = kmap_atomic(page);
	consumed = ap->ops->sff_data_xfer(qc, buf + offset, count, rw);
	kunmap_atomic(buf);

	bytes -= min(bytes, consumed);
	qc->curbytes += count;
	qc->cursg_ofs += count;

	if (qc->cursg_ofs == sg->length) {
		qc->cursg = sg_next(qc->cursg);
		qc->cursg_ofs = 0;
	}

	/*
	 * There used to be a  WARN_ON_ONCE(qc->cursg && count != consumed);
	 * Unfortunately __atapi_pio_bytes doesn't know enough to do the WARN
	 * check correctly as it doesn't know if it is the last request being
	 * made. Somebody should implement a proper sanity check.
	 */
	if (bytes)
		goto next_sg;
	return 0;
}