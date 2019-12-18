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
struct file {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ FILE_MMAP ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/ * bufpos ; 
 scalar_t__ bufrem ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 scalar_t__ filebehave ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsiz ; 
 int /*<<< orphan*/ * lnbuf ; 
 scalar_t__ lnbuflen ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
grep_close(struct file *f)
{

	close(f->fd);

	/* Reset read buffer and line buffer */
	if (filebehave == FILE_MMAP) {
		munmap(buffer, fsiz);
		buffer = NULL;
	}
	bufpos = buffer;
	bufrem = 0;

	free(lnbuf);
	lnbuf = NULL;
	lnbuflen = 0;
}