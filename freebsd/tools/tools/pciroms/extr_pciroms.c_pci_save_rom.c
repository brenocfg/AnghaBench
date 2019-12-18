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
 void* MAP_FAILED ; 
 int MAP_NOCORE ; 
 int MAP_SHARED ; 
 int O_CREAT ; 
 int O_NOFOLLOW ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  PROT_READ ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  _PATH_DEVMEM ; 
 scalar_t__ base_addr ; 
 int /*<<< orphan*/  close (int) ; 
 void* mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int open (char*,int,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int write (int,void*,int) ; 

__attribute__((used)) static int
pci_save_rom(char *filename, int romsize)
{
	int	 fd, mem_fd, err;
	void	*map_addr;

	fd = err = mem_fd = -1;
	map_addr = MAP_FAILED;

	if ((mem_fd = open(_PATH_DEVMEM, O_RDONLY)) == -1) {
		perror("open");
		return -1;
	}

	map_addr = mmap(NULL, romsize, PROT_READ, MAP_SHARED|MAP_NOCORE,
	    mem_fd, base_addr);

	/* Dump ROM aperture to a file. */
	if ((fd = open(filename, O_CREAT|O_RDWR|O_TRUNC|O_NOFOLLOW,
	    S_IRUSR|S_IWUSR)) == -1) {
		perror("open");
		goto cleanup;
	}

	if (write(fd, map_addr, romsize) != romsize)
		perror("write");

	err = 0;
cleanup:
	if (fd != -1)
		close(fd);

	if (map_addr != MAP_FAILED)
		munmap((void *)base_addr, romsize);

	if (mem_fd != -1)
		close(mem_fd);

	return err;
}