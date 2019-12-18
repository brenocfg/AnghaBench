#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct atari_format_descr {int track; int head; int sect_offset; } ;
struct TYPE_9__ {int blocks; int spt; } ;
struct TYPE_8__ {scalar_t__ drive_types; int index; } ;
struct TYPE_7__ {TYPE_1__* disk; } ;
struct TYPE_6__ {struct request_queue* queue; } ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int BufferDrive ; 
 scalar_t__ DriveType ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FILL (int,int) ; 
 scalar_t__ FormatError ; 
 int /*<<< orphan*/  IRQ_MFP_FDC ; 
 int IsFormatting ; 
 int NUM_DISK_MINORS ; 
 int ReqSide ; 
 int ReqTrack ; 
 unsigned char* TrackBuffer ; 
 TYPE_4__* UDT ; 
 TYPE_4__* atari_disk_type ; 
 int /*<<< orphan*/  atari_turnon_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_quiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (struct request_queue*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_fd_action (int) ; 
 int /*<<< orphan*/  floppy_irq ; 
 int /*<<< orphan*/  format_wait ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_3__* minor2disktype ; 
 int /*<<< orphan*/  motor_off_timer ; 
 int /*<<< orphan*/  stdma_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* unit ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_format(int drive, int type, struct atari_format_descr *desc)
{
	struct request_queue *q = unit[drive].disk->queue;
	unsigned char	*p;
	int sect, nsect;
	unsigned long	flags;
	int ret;

	blk_mq_freeze_queue(q);
	blk_mq_quiesce_queue(q);

	local_irq_save(flags);
	stdma_lock(floppy_irq, NULL);
	atari_turnon_irq( IRQ_MFP_FDC ); /* should be already, just to be sure */
	local_irq_restore(flags);

	if (type) {
		if (--type >= NUM_DISK_MINORS ||
		    minor2disktype[type].drive_types > DriveType) {
			ret = -EINVAL;
			goto out;
		}
		type = minor2disktype[type].index;
		UDT = &atari_disk_type[type];
	}

	if (!UDT || desc->track >= UDT->blocks/UDT->spt/2 || desc->head >= 2) {
		ret = -EINVAL;
		goto out;
	}

	nsect = UDT->spt;
	p = TrackBuffer;
	/* The track buffer is used for the raw track data, so its
	   contents become invalid! */
	BufferDrive = -1;
	/* stop deselect timer */
	del_timer( &motor_off_timer );

	FILL( 60 * (nsect / 9), 0x4e );
	for( sect = 0; sect < nsect; ++sect ) {
		FILL( 12, 0 );
		FILL( 3, 0xf5 );
		*p++ = 0xfe;
		*p++ = desc->track;
		*p++ = desc->head;
		*p++ = (nsect + sect - desc->sect_offset) % nsect + 1;
		*p++ = 2;
		*p++ = 0xf7;
		FILL( 22, 0x4e );
		FILL( 12, 0 );
		FILL( 3, 0xf5 );
		*p++ = 0xfb;
		FILL( 512, 0xe5 );
		*p++ = 0xf7;
		FILL( 40, 0x4e );
	}
	FILL( TrackBuffer+BUFFER_SIZE-p, 0x4e );

	IsFormatting = 1;
	FormatError = 0;
	ReqTrack = desc->track;
	ReqSide  = desc->head;
	do_fd_action( drive );

	wait_for_completion(&format_wait);

	ret = FormatError ? -EIO : 0;
out:
	blk_mq_unquiesce_queue(q);
	blk_mq_unfreeze_queue(q);
	return ret;
}