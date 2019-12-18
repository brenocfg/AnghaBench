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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int u_int ;

/* Variables and functions */
 int MIN (int,int) ; 
 int NBBY ; 

__attribute__((used)) static uint32_t
rsb_encode(const uint8_t *buf, u_int len, u_int off)
{
	uint32_t val;
	u_int n;

	val = 0;
	for (n = off; n < MIN(len, 4 + off); n++)
		val |= ((uint32_t)buf[n] << ((n - off) * NBBY));

	return val;
}