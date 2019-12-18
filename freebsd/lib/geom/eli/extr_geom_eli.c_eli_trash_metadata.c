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
struct gctl_req {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  overwrites ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 unsigned int G_ELI_OVERWRITES ; 
 int /*<<< orphan*/  arc4random_buf (unsigned char*,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  g_flush (int) ; 
 int g_sectorsize (int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 unsigned char* malloc (int) ; 
 int pwrite (int,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int sysctlbyname (char*,unsigned int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
eli_trash_metadata(struct gctl_req *req, const char *prov, int fd, off_t offset)
{
	unsigned int overwrites;
	unsigned char *sector;
	ssize_t size;
	int error;

	size = sizeof(overwrites);
	if (sysctlbyname("kern.geom.eli.overwrites", &overwrites, &size,
	    NULL, 0) == -1 || overwrites == 0) {
		overwrites = G_ELI_OVERWRITES;
	}

	size = g_sectorsize(fd);
	if (size <= 0) {
		gctl_error(req, "Cannot obtain provider sector size %s: %s.",
		    prov, strerror(errno));
		return (-1);
	}
	sector = malloc(size);
	if (sector == NULL) {
		gctl_error(req, "Cannot allocate %zd bytes of memory.", size);
		return (-1);
	}

	error = 0;
	do {
		arc4random_buf(sector, size);
		if (pwrite(fd, sector, size, offset) != size) {
			if (error == 0)
				error = errno;
		}
		(void)g_flush(fd);
	} while (--overwrites > 0);
	free(sector);
	if (error != 0) {
		gctl_error(req, "Cannot trash metadata on provider %s: %s.",
		    prov, strerror(error));
		return (-1);
	}
	return (0);
}