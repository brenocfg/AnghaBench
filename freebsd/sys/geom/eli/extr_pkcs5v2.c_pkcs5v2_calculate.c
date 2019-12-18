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
typedef  int intmax_t ;

/* Variables and functions */
 int pkcs5v2_probe (int) ; 

int
pkcs5v2_calculate(int usecs)
{
	int iterations, v;

	for (iterations = 1; ; iterations <<= 1) {
		v = pkcs5v2_probe(iterations);
		if (v > 2000000)
			break;
	}
	return (((intmax_t)iterations * (intmax_t)usecs) / v);
}