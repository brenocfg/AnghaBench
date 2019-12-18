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
typedef  int uint64_t ;

/* Variables and functions */
 int EDOOFUS ; 
 int GXEMUL_DISK_DEV_BLOCKSIZE ; 
 int gxemul_disk_read (unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
gxemul_disk_size(unsigned diskid, uint64_t *sizep)
{
	uint64_t offset, ogood;
	uint64_t m, s;
	int error;

	m = 1;
	s = 3;
	ogood = 0;

	for (;;) {
		offset = (ogood * s) + (m * GXEMUL_DISK_DEV_BLOCKSIZE);

		error = gxemul_disk_read(diskid, NULL, offset);
		if (error != 0) {
			if (m == 1 && s == 1) {
				*sizep = ogood + GXEMUL_DISK_DEV_BLOCKSIZE;
				return (0);
			}
			if (m > 1)
				m /= 2;
			if (s > 1)
				s--;
			continue;
		}
		if (ogood == offset) {
			m = 1;
			continue;
		}
		ogood = offset;
		m++;
	}

	return (EDOOFUS);
}