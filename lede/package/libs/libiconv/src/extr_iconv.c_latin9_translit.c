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
typedef  int wchar_t ;

/* Variables and functions */

__attribute__((used)) static inline wchar_t latin9_translit(wchar_t c)
{
	/* a number of trivial iso-8859-15 <> utf-8 transliterations */
	switch (c) {
	case 0x20AC: return 0xA4; /* Euro */
	case 0x0160: return 0xA6; /* S caron */
	case 0x0161: return 0xA8; /* s caron */
	case 0x017D: return 0xB4; /* Z caron */
	case 0x017E: return 0xB8; /* z caron */
	case 0x0152: return 0xBC; /* OE */
	case 0x0153: return 0xBD; /* oe */
	case 0x0178: return 0xBE; /* Y diaeresis */
	default:     return 0xFFFD; /* cannot translate */
	}
}