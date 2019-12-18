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
typedef  int /*<<< orphan*/  val_64 ;
typedef  int /*<<< orphan*/  val_32 ;
typedef  unsigned long uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct region_desc {unsigned long start; unsigned long end; } ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int MAX (int,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 unsigned long be32toh (int /*<<< orphan*/ ) ; 
 void* be64toh (unsigned long) ; 
 int /*<<< orphan*/  host_close (int) ; 
 int host_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int host_read (int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned long*,int) ; 

__attribute__((used)) static uint64_t
kboot_get_phys_load_segment(void)
{
	int fd;
	uint64_t entry[2];
	static uint64_t load_segment = ~(0UL);
	uint64_t val_64;
	uint32_t val_32;
	struct region_desc rsvd_reg[32];
	int rsvd_reg_cnt = 0;
	int ret, a, b;
	uint64_t start, end;

	if (load_segment == ~(0UL)) {

		/* Default load address is 0x00000000 */
		load_segment = 0UL;

		/* Read reserved regions */
		fd = host_open("/proc/device-tree/reserved-ranges", O_RDONLY, 0);
		if (fd >= 0) {
			while (host_read(fd, &entry[0], sizeof(entry)) == sizeof(entry)) {
				rsvd_reg[rsvd_reg_cnt].start = be64toh(entry[0]);
				rsvd_reg[rsvd_reg_cnt].end =
				    be64toh(entry[1]) + rsvd_reg[rsvd_reg_cnt].start - 1;
				rsvd_reg_cnt++;
			}
			host_close(fd);
		}
		/* Read where the kernel ends */
		fd = host_open("/proc/device-tree/chosen/linux,kernel-end", O_RDONLY, 0);
		if (fd >= 0) {
			ret = host_read(fd, &val_64, sizeof(val_64));

			if (ret == sizeof(uint64_t)) {
				rsvd_reg[rsvd_reg_cnt].start = 0;
				rsvd_reg[rsvd_reg_cnt].end = be64toh(val_64) - 1;
			} else {
				memcpy(&val_32, &val_64, sizeof(val_32));
				rsvd_reg[rsvd_reg_cnt].start = 0;
				rsvd_reg[rsvd_reg_cnt].end = be32toh(val_32) - 1;
			}
			rsvd_reg_cnt++;

			host_close(fd);
		}
		/* Read memory size (SOCKET0 only) */
		fd = host_open("/proc/device-tree/memory@0/reg", O_RDONLY, 0);
		if (fd < 0)
			fd = host_open("/proc/device-tree/memory/reg", O_RDONLY, 0);
		if (fd >= 0) {
			ret = host_read(fd, &entry, sizeof(entry));

			/* Memory range in start:length format */
			entry[0] = be64toh(entry[0]);
			entry[1] = be64toh(entry[1]);

			/* Reserve everything what is before start */
			if (entry[0] != 0) {
				rsvd_reg[rsvd_reg_cnt].start = 0;
				rsvd_reg[rsvd_reg_cnt].end = entry[0] - 1;
				rsvd_reg_cnt++;
			}
			/* Reserve everything what is after end */
			if (entry[1] != 0xffffffffffffffffUL) {
				rsvd_reg[rsvd_reg_cnt].start = entry[0] + entry[1];
				rsvd_reg[rsvd_reg_cnt].end = 0xffffffffffffffffUL;
				rsvd_reg_cnt++;
			}

			host_close(fd);
		}

		/* Sort entries in ascending order (bubble) */
		for (a = rsvd_reg_cnt - 1; a > 0; a--) {
			for (b = 0; b < a; b++) {
				if (rsvd_reg[b].start > rsvd_reg[b + 1].start) {
					struct region_desc tmp;
					tmp = rsvd_reg[b];
					rsvd_reg[b] = rsvd_reg[b + 1];
					rsvd_reg[b + 1] = tmp;
				}
			}
		}

		/* Join overlapping/adjacent regions */
		for (a = 0; a < rsvd_reg_cnt - 1; ) {

			if ((rsvd_reg[a + 1].start >= rsvd_reg[a].start) &&
			    ((rsvd_reg[a + 1].start - 1) <= rsvd_reg[a].end)) {
				/* We have overlapping/adjacent regions! */
				rsvd_reg[a].end =
				    MAX(rsvd_reg[a].end, rsvd_reg[a + a].end);

				for (b = a + 1; b < rsvd_reg_cnt - 1; b++)
					rsvd_reg[b] = rsvd_reg[b + 1];
				rsvd_reg_cnt--;
			} else
				a++;
		}

		/* Find the first free region */
		if (rsvd_reg_cnt > 0) {
			start = 0;
			end = rsvd_reg[0].start;
			for (a = 0; a < rsvd_reg_cnt - 1; a++) {
				if ((start >= rsvd_reg[a].start) &&
				    (start <= rsvd_reg[a].end)) {
					start = rsvd_reg[a].end + 1;
					end = rsvd_reg[a + 1].start;
				} else
					break;
			}

			if (start != end) {
				uint64_t align = 64UL*1024UL*1024UL;

				/* Align both to 64MB boundary */
				start = (start + align - 1UL) & ~(align - 1UL);
				end = ((end + 1UL) & ~(align - 1UL)) - 1UL;

				if (start < end)
					load_segment = start;
			}
		}
	}

	return (load_segment);
}