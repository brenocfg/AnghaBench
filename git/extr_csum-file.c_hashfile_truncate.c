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
struct hashfile_checkpoint {scalar_t__ offset; int /*<<< orphan*/  ctx; } ;
struct hashfile {scalar_t__ offset; int /*<<< orphan*/  ctx; scalar_t__ total; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

int hashfile_truncate(struct hashfile *f, struct hashfile_checkpoint *checkpoint)
{
	off_t offset = checkpoint->offset;

	if (ftruncate(f->fd, offset) ||
	    lseek(f->fd, offset, SEEK_SET) != offset)
		return -1;
	f->total = offset;
	f->ctx = checkpoint->ctx;
	f->offset = 0; /* hashflush() was called in checkpoint */
	return 0;
}