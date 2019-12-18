#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct format_descr {scalar_t__ track; scalar_t__ head; } ;
struct TYPE_5__ {scalar_t__ tracks; } ;
struct TYPE_4__ {scalar_t__ track; scalar_t__ head; int sect; int /*<<< orphan*/  fmt_gap; } ;

/* Variables and functions */
 TYPE_3__* DP ; 
 int EINTR ; 
 int EINVAL ; 
 int FD_SIZECODE (TYPE_1__*) ; 
 TYPE_1__* _floppy ; 
 int /*<<< orphan*/ * cont ; 
 scalar_t__* errors ; 
 int /*<<< orphan*/  format_cont ; 
 scalar_t__ format_errors ; 
 struct format_descr format_req ; 
 scalar_t__ lock_fdc (int) ; 
 int /*<<< orphan*/  process_fd_request () ; 
 int /*<<< orphan*/  redo_format ; 
 int /*<<< orphan*/  set_floppy (int) ; 
 int wait_til_done (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_format(int drive, struct format_descr *tmp_format_req)
{
	int ret;

	if (lock_fdc(drive))
		return -EINTR;

	set_floppy(drive);
	if (!_floppy ||
	    _floppy->track > DP->tracks ||
	    tmp_format_req->track >= _floppy->track ||
	    tmp_format_req->head >= _floppy->head ||
	    (_floppy->sect << 2) % (1 << FD_SIZECODE(_floppy)) ||
	    !_floppy->fmt_gap) {
		process_fd_request();
		return -EINVAL;
	}
	format_req = *tmp_format_req;
	format_errors = 0;
	cont = &format_cont;
	errors = &format_errors;
	ret = wait_til_done(redo_format, true);
	if (ret == -EINTR)
		return -EINTR;
	process_fd_request();
	return ret;
}