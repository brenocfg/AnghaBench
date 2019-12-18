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

/* Variables and functions */
 int /*<<< orphan*/  EFTYPE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  _PATH_DEV ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int g_sectorsize (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char *
g_device_path_open(const char *devpath, int *fdp, int dowrite)
{
	char *path;
	int fd;

	/* Make sure that we can fail. */
	if (fdp != NULL)
		*fdp = -1;

	/* Use the device node if we're able to open it. */
	fd = open(devpath, dowrite ? O_RDWR : O_RDONLY);
	if (fd != -1) {
		if ((path = strdup(devpath)) == NULL) {
			close(fd);
			return (NULL);
		}
		goto fd_ok;
	}

	/* If we're not given an absolute path, assume /dev/ prefix. */
	if (*devpath == '/')
		return (NULL);

	asprintf(&path, "%s%s", _PATH_DEV, devpath);
	if (path == NULL)
		return (NULL);
	fd = open(path, dowrite ? O_RDWR : O_RDONLY);
	if (fd == -1) {
		free(path);
		return (NULL);
	}

fd_ok:
	/*
	 * Let try to get sectorsize, which will prove it is a GEOM provider.
	 */
	if (g_sectorsize(fd) == -1) {
		free(path);
		close(fd);
		errno = EFTYPE;
		return (NULL);
	}
	if (fdp != NULL)
		*fdp = fd;
	else
		close(fd);
	return (path);
}