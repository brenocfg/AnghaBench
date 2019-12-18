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
typedef  int ufs2_daddr_t ;
struct uufsd {int d_bsize; int /*<<< orphan*/  d_fd; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct uufsd*,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int pread (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

ssize_t
bread(struct uufsd *disk, ufs2_daddr_t blockno, void *data, size_t size)
{
	void *p2;
	ssize_t cnt;

	ERROR(disk, NULL);

	p2 = data;
	/*
	 * XXX: various disk controllers require alignment of our buffer
	 * XXX: which is stricter than struct alignment.
	 * XXX: Bounce the buffer if not 64 byte aligned.
	 * XXX: this can be removed if/when the kernel is fixed
	 */
	if (((intptr_t)data) & 0x3f) {
		p2 = malloc(size);
		if (p2 == NULL) {
			ERROR(disk, "allocate bounce buffer");
			goto fail;
		}
	}
	cnt = pread(disk->d_fd, p2, size, (off_t)(blockno * disk->d_bsize));
	if (cnt == -1) {
		ERROR(disk, "read error from block device");
		goto fail;
	}
	if (cnt == 0) {
		ERROR(disk, "end of file from block device");
		goto fail;
	}
	if ((size_t)cnt != size) {
		ERROR(disk, "short read or read error from block device");
		goto fail;
	}
	if (p2 != data) {
		memcpy(data, p2, size);
		free(p2);
	}
	return (cnt);
fail:	memset(data, 0, size);
	if (p2 != data) {
		free(p2);
	}
	return (-1);
}