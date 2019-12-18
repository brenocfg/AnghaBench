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
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int pwrite (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 
 int ufs_disk_write (struct uufsd*) ; 

ssize_t
bwrite(struct uufsd *disk, ufs2_daddr_t blockno, const void *data, size_t size)
{
	ssize_t cnt;
	int rv;
	void *p2 = NULL;

	ERROR(disk, NULL);

	rv = ufs_disk_write(disk);
	if (rv == -1) {
		ERROR(disk, "failed to open disk for writing");
		return (-1);
	}

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
			return (-1);
		}
		memcpy(p2, data, size);
		data = p2;
	}
	cnt = pwrite(disk->d_fd, data, size, (off_t)(blockno * disk->d_bsize));
	if (p2 != NULL)
		free(p2);
	if (cnt == -1) {
		ERROR(disk, "write error to block device");
		return (-1);
	}
	if ((size_t)cnt != size) {
		ERROR(disk, "short write to block device");
		return (-1);
	}

	return (cnt);
}