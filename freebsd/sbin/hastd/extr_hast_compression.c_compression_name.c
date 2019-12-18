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
#define  HAST_COMPRESSION_HOLE 130 
#define  HAST_COMPRESSION_LZF 129 
#define  HAST_COMPRESSION_NONE 128 

const char *
compression_name(int num)
{

	switch (num) {
	case HAST_COMPRESSION_NONE:
		return ("none");
	case HAST_COMPRESSION_HOLE:
		return ("hole");
	case HAST_COMPRESSION_LZF:
		return ("lzf");
	}
	return ("unknown");
}