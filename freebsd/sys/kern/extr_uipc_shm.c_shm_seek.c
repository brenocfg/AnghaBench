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
struct TYPE_2__ {scalar_t__ tdu_off; } ;
struct thread {TYPE_1__ td_uretoff; } ;
struct shmfd {scalar_t__ shm_size; } ;
struct file {struct shmfd* f_data; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  FOF_NOUPDATE ; 
#define  L_INCR 130 
#define  L_SET 129 
#define  L_XTND 128 
 scalar_t__ OFF_MAX ; 
 scalar_t__ foffset_lock (struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foffset_unlock (struct file*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
shm_seek(struct file *fp, off_t offset, int whence, struct thread *td)
{
	struct shmfd *shmfd;
	off_t foffset;
	int error;

	shmfd = fp->f_data;
	foffset = foffset_lock(fp, 0);
	error = 0;
	switch (whence) {
	case L_INCR:
		if (foffset < 0 ||
		    (offset > 0 && foffset > OFF_MAX - offset)) {
			error = EOVERFLOW;
			break;
		}
		offset += foffset;
		break;
	case L_XTND:
		if (offset > 0 && shmfd->shm_size > OFF_MAX - offset) {
			error = EOVERFLOW;
			break;
		}
		offset += shmfd->shm_size;
		break;
	case L_SET:
		break;
	default:
		error = EINVAL;
	}
	if (error == 0) {
		if (offset < 0 || offset > shmfd->shm_size)
			error = EINVAL;
		else
			td->td_uretoff.tdu_off = offset;
	}
	foffset_unlock(fp, offset, error != 0 ? FOF_NOUPDATE : 0);
	return (error);
}