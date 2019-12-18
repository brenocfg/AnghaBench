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
struct std_metadata {int /*<<< orphan*/  md_magic; } ;
typedef  int ssize_t ;
typedef  int off_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (unsigned char*,unsigned char*,size_t) ; 
 int errno ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  g_close (int) ; 
 int g_mediasize (int) ; 
 int g_open (char const*,int /*<<< orphan*/ ) ; 
 int g_sectorsize (int) ; 
 unsigned char* malloc (int) ; 
 int pread (int,unsigned char*,int,int) ; 
 int /*<<< orphan*/  std_metadata_decode (unsigned char*,struct std_metadata*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
g_metadata_read(const char *name, unsigned char *md, size_t size,
    const char *magic)
{
	struct std_metadata stdmd;
	unsigned char *sector;
	ssize_t sectorsize;
	off_t mediasize;
	int error, fd;

	sector = NULL;
	error = 0;

	fd = g_open(name, 0);
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
	if (pread(fd, sector, sectorsize, mediasize - sectorsize) !=
	    sectorsize) {
		error = errno;
		goto out;
	}
	if (magic != NULL) {
		std_metadata_decode(sector, &stdmd);
		if (strcmp(stdmd.md_magic, magic) != 0) {
			error = EINVAL;
			goto out;
		}
	}
	bcopy(sector, md, size);
out:
	if (sector != NULL)
		free(sector);
	g_close(fd);
	return (error);
}