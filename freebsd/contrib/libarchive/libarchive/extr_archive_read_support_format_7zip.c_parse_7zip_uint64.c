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
struct archive_read {int dummy; } ;

/* Variables and functions */
 unsigned char* header_bytes (struct archive_read*,int) ; 

__attribute__((used)) static int
parse_7zip_uint64(struct archive_read *a, uint64_t *val)
{
	const unsigned char *p;
	unsigned char avail, mask;
	int i;

	if ((p = header_bytes(a, 1)) == NULL)
		return (-1);
	avail = *p;
	mask = 0x80;
	*val = 0;
	for (i = 0; i < 8; i++) {
		if (avail & mask) {
			if ((p = header_bytes(a, 1)) == NULL)
				return (-1);
			*val |= ((uint64_t)*p) << (8 * i);
			mask >>= 1;
			continue;
		}
		*val += ((uint64_t)(avail & (mask -1))) << (8 * i);
		break;
	}
	return (0);
}