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

int DDSBigLong( int src ){
	return ( ( src & 0xFF000000 ) >> 24 ) |
		   ( ( src & 0x00FF0000 ) >> 8 ) |
		   ( ( src & 0x0000FF00 ) << 8 ) |
		   ( ( src & 0x000000FF ) << 24 );
}