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
struct floppy_struct {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 int ENODEV ; 
 struct floppy_struct** current_type ; 
 struct floppy_struct* floppy_type ; 
 scalar_t__ lock_fdc (int) ; 
 int poll_drive (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_fd_request () ; 

__attribute__((used)) static int get_floppy_geometry(int drive, int type, struct floppy_struct **g)
{
	if (type)
		*g = &floppy_type[type];
	else {
		if (lock_fdc(drive))
			return -EINTR;
		if (poll_drive(false, 0) == -EINTR)
			return -EINTR;
		process_fd_request();
		*g = current_type[drive];
	}
	if (!*g)
		return -ENODEV;
	return 0;
}