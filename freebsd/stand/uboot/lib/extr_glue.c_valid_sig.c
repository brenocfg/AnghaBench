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
struct api_signature {scalar_t__ checksum; } ;

/* Variables and functions */
 scalar_t__ crc32 (void*,int) ; 

__attribute__((used)) static int
valid_sig(struct api_signature *sig)
{
	uint32_t checksum;
	struct api_signature s;

	if (sig == NULL)
		return (0);
	/*
	 * Clear the checksum field (in the local copy) so as to calculate the
	 * CRC with the same initial contents as at the time when the sig was
	 * produced
	 */
	s = *sig;
	s.checksum = 0;

	checksum = crc32((void *)&s, sizeof(struct api_signature));

	if (checksum != sig->checksum)
		return (0);

	return (1);
}