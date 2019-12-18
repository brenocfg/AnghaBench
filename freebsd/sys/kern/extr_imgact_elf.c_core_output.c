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
struct coredump_params {int /*<<< orphan*/ * comp; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_comm; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int compress_chunk (struct coredump_params*,void*,void*,size_t) ; 
 int core_write (struct coredump_params*,void*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* curproc ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,void*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 void* zero_region ; 

__attribute__((used)) static int
core_output(void *base, size_t len, off_t offset, struct coredump_params *p,
    void *tmpbuf)
{
	int error;

	if (p->comp != NULL)
		return (compress_chunk(p, base, tmpbuf, len));

	/*
	 * EFAULT is a non-fatal error that we can get, for example,
	 * if the segment is backed by a file but extends beyond its
	 * end.
	 */
	error = core_write(p, base, len, offset, UIO_USERSPACE);
	if (error == EFAULT) {
		log(LOG_WARNING, "Failed to fully fault in a core file segment "
		    "at VA %p with size 0x%zx to be written at offset 0x%jx "
		    "for process %s\n", base, len, offset, curproc->p_comm);

		/*
		 * Write a "real" zero byte at the end of the target region
		 * in the case this is the last segment.
		 * The intermediate space will be implicitly zero-filled.
		 */
		error = core_write(p, zero_region, 1, offset + len - 1,
		    UIO_SYSSPACE);
	}
	return (error);
}