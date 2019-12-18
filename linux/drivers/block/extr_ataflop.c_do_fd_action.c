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
struct TYPE_4__ {int track; } ;
struct TYPE_3__ {int stretch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 scalar_t__ IS_BUFFERED (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IsFormatting ; 
 scalar_t__ READ ; 
 scalar_t__ ReqCmd ; 
 scalar_t__ ReqCnt ; 
 int /*<<< orphan*/  ReqData ; 
 int /*<<< orphan*/  ReqSector ; 
 int /*<<< orphan*/  ReqSide ; 
 int ReqTrack ; 
 int /*<<< orphan*/  SECTOR_BUFFER (int /*<<< orphan*/ ) ; 
 int SelectedDrive ; 
 TYPE_2__ UD ; 
 TYPE_1__* UDT ; 
 scalar_t__ UseTrackbuffer ; 
 scalar_t__ blk_rq_cur_sectors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_calibrate () ; 
 int /*<<< orphan*/  fd_end_request_cur (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_request ; 
 int /*<<< orphan*/  fd_rwsec () ; 
 int /*<<< orphan*/  fd_seek () ; 
 int /*<<< orphan*/  fd_select_drive (int) ; 
 int /*<<< orphan*/  fd_writetrack () ; 
 int /*<<< orphan*/  setup_req_params (int) ; 

__attribute__((used)) static void do_fd_action( int drive )
{
	DPRINT(("do_fd_action\n"));
	
	if (UseTrackbuffer && !IsFormatting) {
	repeat:
	    if (IS_BUFFERED( drive, ReqSide, ReqTrack )) {
		if (ReqCmd == READ) {
		    copy_buffer( SECTOR_BUFFER(ReqSector), ReqData );
		    if (++ReqCnt < blk_rq_cur_sectors(fd_request)) {
			/* read next sector */
			setup_req_params( drive );
			goto repeat;
		    }
		    else {
			/* all sectors finished */
			fd_end_request_cur(BLK_STS_OK);
			return;
		    }
		}
		else {
		    /* cmd == WRITE, pay attention to track buffer
		     * consistency! */
		    copy_buffer( ReqData, SECTOR_BUFFER(ReqSector) );
		}
	    }
	}

	if (SelectedDrive != drive)
		fd_select_drive( drive );
    
	if (UD.track == -1)
		fd_calibrate();
	else if (UD.track != ReqTrack << UDT->stretch)
		fd_seek();
	else if (IsFormatting)
		fd_writetrack();
	else
		fd_rwsec();
}