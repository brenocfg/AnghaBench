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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static int
contigmask(uint8_t *p, int len)
{
	int i, n;

	for (i = 0; i < len ; i++)
		if ( (p[i/8] & (1 << (7 - (i%8)))) == 0) /* first bit unset */
			break;
	for (n= i + 1; n < len; n++)
		if ( (p[n/8] & (1 << (7 - (n % 8)))) != 0)
			return (-1); /* mask not contiguous */
	return (i);
}