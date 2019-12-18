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
#define  HAST_CHECKSUM_CRC32 130 
#define  HAST_CHECKSUM_NONE 129 
#define  HAST_CHECKSUM_SHA256 128 

const char *
checksum_name(int num)
{

	switch (num) {
	case HAST_CHECKSUM_NONE:
		return ("none");
	case HAST_CHECKSUM_CRC32:
		return ("crc32");
	case HAST_CHECKSUM_SHA256:
		return ("sha256");
	}
	return ("unknown");
}