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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 char const* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dump_amd_msr_pm (char const*,int) ; 
 int /*<<< orphan*/  dump_intel_msr_pm (char const*,int) ; 
 char* mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,int) ; 
 int open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int
dump_msr_bitmap(int vcpu, uint64_t addr, bool cpu_intel)
{
	int error, fd, map_size;
	const char *bitmap;

	error = -1;
	bitmap = MAP_FAILED;

	fd = open("/dev/mem", O_RDONLY, 0);
	if (fd < 0) {
		perror("Couldn't open /dev/mem");
		goto done;
	}

	if (cpu_intel)
		map_size = PAGE_SIZE;
	else
		map_size = 2 * PAGE_SIZE;

	bitmap = mmap(NULL, map_size, PROT_READ, MAP_SHARED, fd, addr);
	if (bitmap == MAP_FAILED) {
		perror("mmap failed");
		goto done;
	}
	
	if (cpu_intel)
		dump_intel_msr_pm(bitmap, vcpu);
	else	
		dump_amd_msr_pm(bitmap, vcpu);

	error = 0;
done:
	if (bitmap != MAP_FAILED)
		munmap((void *)bitmap, map_size);
	if (fd >= 0)
		close(fd);

	return (error);
}