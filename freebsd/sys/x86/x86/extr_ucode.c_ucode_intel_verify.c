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
typedef  int uint32_t ;
struct ucode_intel_header {int total_size; int header_version; } ;

/* Variables and functions */
 int UCODE_INTEL_DEFAULT_DATA_SIZE ; 

__attribute__((used)) static int
ucode_intel_verify(struct ucode_intel_header *hdr, size_t resid)
{
	uint32_t cksum, *data, size;
	int i;

	if (resid < sizeof(struct ucode_intel_header))
		return (1);
	size = hdr->total_size;
	if (size == 0)
		size = UCODE_INTEL_DEFAULT_DATA_SIZE +
		    sizeof(struct ucode_intel_header);

	if (hdr->header_version != 1)
		return (1);
	if (size % 16 != 0)
		return (1);
	if (resid < size)
		return (1);

	cksum = 0;
	data = (uint32_t *)hdr;
	for (i = 0; i < size / sizeof(uint32_t); i++)
		cksum += data[i];
	if (cksum != 0)
		return (1);
	return (0);
}