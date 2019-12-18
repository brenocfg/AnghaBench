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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  tmp ;
struct executable {int x_checksum_off; int x_len; scalar_t__ x_buf; int /*<<< orphan*/  x_checksum_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  range_check (struct executable const*,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint32_t
compute_checksum(const struct executable *x)
{
	uint32_t cksum = 0;
	uint16_t tmp;
	int i;

	range_check(x, x->x_checksum_off, x->x_checksum_len, "PE checksum");

	assert(x->x_checksum_off % 2 == 0);

	for (i = 0; i + sizeof(tmp) < x->x_len; i += 2) {
		/*
		 * Don't checksum the checksum.  The +2 is because the checksum
		 * is 4 bytes, and here we're iterating over 2 byte chunks.
		 */
		if (i == x->x_checksum_off || i == x->x_checksum_off + 2) {
			tmp = 0;
		} else {
			assert(i + sizeof(tmp) <= x->x_len);
			memcpy(&tmp, x->x_buf + i, sizeof(tmp));
		}

		cksum += tmp;
		cksum += cksum >> 16;
		cksum &= 0xffff;
	}

	cksum += cksum >> 16;
	cksum &= 0xffff;

	cksum += x->x_len;

	return (cksum);
}