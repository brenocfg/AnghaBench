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
 int /*<<< orphan*/  _7ZIP_SIGNATURE ; 
 int /*<<< orphan*/  archive_le32dec (char const*) ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
check_7zip_header_in_sfx(const char *p)
{
	switch ((unsigned char)p[5]) {
	case 0x1C:
		if (memcmp(p, _7ZIP_SIGNATURE, 6) != 0)
			return (6);
		/*
		 * Test the CRC because its extraction code has 7-Zip
		 * Magic Code, so we should do this in order not to
		 * make a mis-detection.
		 */
		if (crc32(0, (const unsigned char *)p + 12, 20)
			!= archive_le32dec(p + 8))
			return (6);
		/* Hit the header! */
		return (0);
	case 0x37: return (5);
	case 0x7A: return (4);
	case 0xBC: return (3);
	case 0xAF: return (2);
	case 0x27: return (1);
	default: return (6);
	}
}