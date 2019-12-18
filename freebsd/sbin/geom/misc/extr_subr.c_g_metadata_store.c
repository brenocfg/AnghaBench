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
typedef  int ssize_t ;
typedef  int off_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (unsigned char const*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  bzero (unsigned char*,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  g_close (int) ; 
 int /*<<< orphan*/  g_flush (int) ; 
 int g_mediasize (int) ; 
 int g_open (char const*,int) ; 
 int g_sectorsize (int) ; 
 unsigned char* malloc (int) ; 
 int pwrite (int,unsigned char*,int,int) ; 

int
g_metadata_store(const char *name, const unsigned char *md, size_t size)
{
	unsigned char *sector;
	ssize_t sectorsize;
	off_t mediasize;
	int error, fd;

	sector = NULL;
	error = 0;

	fd = g_open(name, 1);
	if (fd == -1)
		return (errno);
	mediasize = g_mediasize(fd);
	if (mediasize == -1) {
		error = errno;
		goto out;
	}
	sectorsize = g_sectorsize(fd);
	if (sectorsize == -1) {
		error = errno;
		goto out;
	}
	assert(sectorsize >= (ssize_t)size);
	sector = malloc(sectorsize);
	if (sector == NULL) {
		error = ENOMEM;
		goto out;
	}
	bcopy(md, sector, size);
	bzero(sector + size, sectorsize - size);
	if (pwrite(fd, sector, sectorsize, mediasize - sectorsize) !=
	    sectorsize) {
		error = errno;
		goto out;
	}
	(void)g_flush(fd);
out:
	if (sector != NULL)
		free(sector);
	(void)g_close(fd);
	return (error);
}