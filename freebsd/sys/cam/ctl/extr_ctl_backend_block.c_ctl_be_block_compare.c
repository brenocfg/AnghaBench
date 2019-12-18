#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union ctl_io {int /*<<< orphan*/  scsiio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct ctl_be_block_io {int num_segs; TYPE_1__* sg_segs; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_4__ {scalar_t__ ptr; } ;
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int CTLBLK_HALF_SEGS ; 
 TYPE_2__* PRIV (union ctl_io*) ; 
 int /*<<< orphan*/  SSD_ELEM_INFO ; 
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_KEY_MISCOMPARE ; 
 scalar_t__ cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ctl_set_sense (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_success (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_u64to8b (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ctl_be_block_compare(union ctl_io *io)
{
	struct ctl_be_block_io *beio;
	uint64_t off, res;
	int i;
	uint8_t info[8];

	beio = (struct ctl_be_block_io *)PRIV(io)->ptr;
	off = 0;
	for (i = 0; i < beio->num_segs; i++) {
		res = cmp(beio->sg_segs[i].addr,
		    beio->sg_segs[i + CTLBLK_HALF_SEGS].addr,
		    beio->sg_segs[i].len);
		off += res;
		if (res < beio->sg_segs[i].len)
			break;
	}
	if (i < beio->num_segs) {
		scsi_u64to8b(off, info);
		ctl_set_sense(&io->scsiio, /*current_error*/ 1,
		    /*sense_key*/ SSD_KEY_MISCOMPARE,
		    /*asc*/ 0x1D, /*ascq*/ 0x00,
		    /*type*/ SSD_ELEM_INFO,
		    /*size*/ sizeof(info), /*data*/ &info,
		    /*type*/ SSD_ELEM_NONE);
	} else
		ctl_set_success(&io->scsiio);
}