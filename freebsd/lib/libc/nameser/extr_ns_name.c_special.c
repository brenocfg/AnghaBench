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

__attribute__((used)) static int
special(int ch) {
	switch (ch) {
	case 0x22: /*%< '"' */
	case 0x2E: /*%< '.' */
	case 0x3B: /*%< ';' */
	case 0x5C: /*%< '\\' */
	case 0x28: /*%< '(' */
	case 0x29: /*%< ')' */
	/* Special modifiers in zone files. */
	case 0x40: /*%< '@' */
	case 0x24: /*%< '$' */
		return (1);
	default:
		return (0);
	}
}