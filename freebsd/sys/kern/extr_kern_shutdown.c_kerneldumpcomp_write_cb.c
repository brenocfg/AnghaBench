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
typedef  int /*<<< orphan*/  uint8_t ;
struct dumperinfo {size_t blocksize; TYPE_1__* kdcomp; int /*<<< orphan*/  blockbuf; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {size_t kdc_resid; } ;

/* Variables and functions */
 int EAGAIN ; 
 int _dump_append (struct dumperinfo*,void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t rounddown (size_t,size_t) ; 

__attribute__((used)) static int
kerneldumpcomp_write_cb(void *base, size_t length, off_t offset, void *arg)
{
	struct dumperinfo *di;
	size_t resid, rlength;
	int error;

	di = arg;

	if (length % di->blocksize != 0) {
		/*
		 * This must be the final write after flushing the compression
		 * stream. Write as many full blocks as possible and stash the
		 * residual data in the dumper's block buffer. It will be
		 * padded and written in dump_finish().
		 */
		rlength = rounddown(length, di->blocksize);
		if (rlength != 0) {
			error = _dump_append(di, base, 0, rlength);
			if (error != 0)
				return (error);
		}
		resid = length - rlength;
		memmove(di->blockbuf, (uint8_t *)base + rlength, resid);
		di->kdcomp->kdc_resid = resid;
		return (EAGAIN);
	}
	return (_dump_append(di, base, 0, length));
}