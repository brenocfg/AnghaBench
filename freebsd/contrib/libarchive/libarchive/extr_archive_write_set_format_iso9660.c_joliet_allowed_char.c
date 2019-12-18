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

__attribute__((used)) static inline int
joliet_allowed_char(unsigned char high, unsigned char low)
{
	int utf16 = (high << 8) | low;

	if (utf16 <= 0x001F)
		return (0);

	switch (utf16) {
	case 0x002A: /* '*' */
	case 0x002F: /* '/' */
	case 0x003A: /* ':' */
	case 0x003B: /* ';' */
	case 0x003F: /* '?' */
	case 0x005C: /* '\' */
		return (0);/* Not allowed. */
	}
	return (1);
}