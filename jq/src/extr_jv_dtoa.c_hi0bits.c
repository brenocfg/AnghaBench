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
struct dtoa_context {int dummy; } ;
typedef  int ULong ;

/* Variables and functions */

__attribute__((used)) static int
hi0bits
 (struct dtoa_context* C, ULong x)
{
	int k = 0;

	if (!(x & 0xffff0000)) {
		k = 16;
		x <<= 16;
		}
	if (!(x & 0xff000000)) {
		k += 8;
		x <<= 8;
		}
	if (!(x & 0xf0000000)) {
		k += 4;
		x <<= 4;
		}
	if (!(x & 0xc0000000)) {
		k += 2;
		x <<= 2;
		}
	if (!(x & 0x80000000)) {
		k++;
		if (!(x & 0x40000000))
			return 32;
		}
	return k;
	}