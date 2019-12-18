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
struct ustar_header {scalar_t__ chksum; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int ustar_header_chksum(const struct ustar_header *header)
{
	const unsigned char *p = (const unsigned char *)header;
	unsigned int chksum = 0;
	while (p < (const unsigned char *)header->chksum)
		chksum += *p++;
	chksum += sizeof(header->chksum) * ' ';
	p += sizeof(header->chksum);
	while (p < (const unsigned char *)header + sizeof(struct ustar_header))
		chksum += *p++;
	return chksum;
}