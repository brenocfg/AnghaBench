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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int git__tolower (int) ; 
 int git__utf8_iterate (int /*<<< orphan*/  const*,int,int*) ; 

__attribute__((used)) static int32_t next_hfs_char(const char **in, size_t *len)
{
	while (*len) {
		int32_t codepoint;
		int cp_len = git__utf8_iterate((const uint8_t *)(*in), (int)(*len), &codepoint);
		if (cp_len < 0)
			return -1;

		(*in) += cp_len;
		(*len) -= cp_len;

		/* these code points are ignored completely */
		switch (codepoint) {
		case 0x200c: /* ZERO WIDTH NON-JOINER */
		case 0x200d: /* ZERO WIDTH JOINER */
		case 0x200e: /* LEFT-TO-RIGHT MARK */
		case 0x200f: /* RIGHT-TO-LEFT MARK */
		case 0x202a: /* LEFT-TO-RIGHT EMBEDDING */
		case 0x202b: /* RIGHT-TO-LEFT EMBEDDING */
		case 0x202c: /* POP DIRECTIONAL FORMATTING */
		case 0x202d: /* LEFT-TO-RIGHT OVERRIDE */
		case 0x202e: /* RIGHT-TO-LEFT OVERRIDE */
		case 0x206a: /* INHIBIT SYMMETRIC SWAPPING */
		case 0x206b: /* ACTIVATE SYMMETRIC SWAPPING */
		case 0x206c: /* INHIBIT ARABIC FORM SHAPING */
		case 0x206d: /* ACTIVATE ARABIC FORM SHAPING */
		case 0x206e: /* NATIONAL DIGIT SHAPES */
		case 0x206f: /* NOMINAL DIGIT SHAPES */
		case 0xfeff: /* ZERO WIDTH NO-BREAK SPACE */
			continue;
		}

		/* fold into lowercase -- this will only fold characters in
		 * the ASCII range, which is perfectly fine, because the
		 * git folder name can only be composed of ascii characters
		 */
		return git__tolower(codepoint);
	}
	return 0; /* NULL byte -- end of string */
}