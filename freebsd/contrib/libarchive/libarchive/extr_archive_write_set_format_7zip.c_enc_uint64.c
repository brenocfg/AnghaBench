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
typedef  unsigned int uint8_t ;
typedef  unsigned int uint64_t ;
struct archive_write {int dummy; } ;
typedef  int /*<<< orphan*/  numdata ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_Z_RUN ; 
 scalar_t__ compress_out (struct archive_write*,unsigned int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enc_uint64(struct archive_write *a, uint64_t val)
{
	unsigned mask = 0x80;
	uint8_t numdata[9];
	int i;

	numdata[0] = 0;
	for (i = 1; i < (int)sizeof(numdata); i++) {
		if (val < mask) {
			numdata[0] |= (uint8_t)val;
			break;
		}
		numdata[i] = (uint8_t)val;
		val >>= 8;
		numdata[0] |= mask;
		mask >>= 1;
	}
	return ((int)compress_out(a, numdata, i, ARCHIVE_Z_RUN));
}