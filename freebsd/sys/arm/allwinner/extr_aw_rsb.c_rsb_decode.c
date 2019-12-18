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
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t u_int ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 size_t NBBY ; 

__attribute__((used)) static void
rsb_decode(const uint32_t val, uint8_t *buf, u_int len, u_int off)
{
	u_int n;

	for (n = off; n < MIN(len, 4 + off); n++)
		buf[n] = (val >> ((n - off) * NBBY)) & 0xff;
}