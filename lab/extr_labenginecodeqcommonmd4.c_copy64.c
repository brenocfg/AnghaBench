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
typedef  scalar_t__ byte ;

/* Variables and functions */

__attribute__((used)) static void copy64(uint32_t *M, byte *in)
{
	int i;

	for (i=0;i<16;i++)
		M[i] =
			((uint32_t)in[i*4+3] << 24) |
			((uint32_t)in[i*4+2] << 16) |
			((uint32_t)in[i*4+1] <<	 8) |
			((uint32_t)in[i*4+0] <<	 0) ;
}