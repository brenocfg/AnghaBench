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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_ELI_MAGIC ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  explicit_bzero (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fsync (int) ; 
 scalar_t__ g_get_sectorsize (char const*) ; 
 int g_metadata_read (char const*,unsigned char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*,...) ; 
 unsigned char* malloc (scalar_t__) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 scalar_t__ write (int,unsigned char*,scalar_t__) ; 

__attribute__((used)) static int
eli_backup_create(struct gctl_req *req, const char *prov, const char *file)
{
	unsigned char *sector;
	ssize_t secsize;
	int error, filefd, ret;

	ret = -1;
	filefd = -1;
	sector = NULL;
	secsize = 0;

	secsize = g_get_sectorsize(prov);
	if (secsize == 0) {
		gctl_error(req, "Cannot get informations about %s: %s.", prov,
		    strerror(errno));
		goto out;
	}
	sector = malloc(secsize);
	if (sector == NULL) {
		gctl_error(req, "Cannot allocate memory.");
		goto out;
	}
	/* Read metadata from the provider. */
	error = g_metadata_read(prov, sector, secsize, G_ELI_MAGIC);
	if (error != 0) {
		gctl_error(req, "Unable to read metadata from %s: %s.", prov,
		    strerror(error));
		goto out;
	}

	filefd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	if (filefd == -1) {
		gctl_error(req, "Unable to open %s: %s.", file,
		    strerror(errno));
		goto out;
	}
	/* Write metadata to the destination file. */
	if (write(filefd, sector, secsize) != secsize) {
		gctl_error(req, "Unable to write to %s: %s.", file,
		    strerror(errno));
		(void)close(filefd);
		(void)unlink(file);
		goto out;
	}
	(void)fsync(filefd);
	(void)close(filefd);
	/* Success. */
	ret = 0;
out:
	if (sector != NULL) {
		explicit_bzero(sector, secsize);
		free(sector);
	}
	return (ret);
}