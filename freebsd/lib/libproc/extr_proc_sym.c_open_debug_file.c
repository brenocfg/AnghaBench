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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFX (char*,char*) ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 size_t PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ crc32_file (int,scalar_t__*) ; 
 int open (char*,int) ; 
 size_t strlcat (char*,char const*,size_t) ; 

__attribute__((used)) static int
open_debug_file(char *path, const char *debugfile, uint32_t crc)
{
	size_t n;
	uint32_t compcrc;
	int fd;

	fd = -1;
	if ((n = strlcat(path, "/", PATH_MAX)) >= PATH_MAX)
		return (fd);
	if (strlcat(path, debugfile, PATH_MAX) >= PATH_MAX)
		goto out;
	if ((fd = open(path, O_RDONLY | O_CLOEXEC)) < 0)
		goto out;
	if (crc32_file(fd, &compcrc) != 0 || crc != compcrc) {
		DPRINTFX("ERROR: CRC32 mismatch for %s", path);
		(void)close(fd);
		fd = -1;
	}
out:
	path[n] = '\0';
	return (fd);
}