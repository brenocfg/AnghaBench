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
struct ata_queued_cmd {int /*<<< orphan*/ * cdb; } ;

/* Variables and functions */
 scalar_t__ ATAPI_MISC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ali_atapi_dma ; 
 scalar_t__ atapi_cmd_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ali_check_atapi_dma(struct ata_queued_cmd *qc)
{
	if (!ali_atapi_dma) {
		/* FIXME: pata_ali can't do ATAPI DMA reliably but the
		 * IDE alim15x3 driver can.  I tried lots of things
		 * but couldn't find what the actual difference was.
		 * If you got an idea, please write it to
		 * linux-ide@vger.kernel.org and cc htejun@gmail.com.
		 *
		 * Disable ATAPI DMA for now.
		 */
		return -EOPNOTSUPP;
	}

	/* If its not a media command, its not worth it */
	if (atapi_cmd_type(qc->cdb[0]) == ATAPI_MISC)
		return -EOPNOTSUPP;
	return 0;
}