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

/* Variables and functions */

void
put_msb_long(
	unsigned char **bufpp,
	long val
	)
{
  *((*bufpp)++) = (unsigned char)((val >> 24) & 0xFF);
  *((*bufpp)++) = (unsigned char)((val >> 16) & 0xFF);
  *((*bufpp)++) = (unsigned char)((val >> 8 ) & 0xFF);
  *((*bufpp)++) = (unsigned char)( val        & 0xFF);
}