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
 int /*<<< orphan*/  ESCAPE ; 
#define  UCS2_BIT 129 
 int /*<<< orphan*/  UCS2_ESC ; 
#define  UCS4_BIT 128 
 int /*<<< orphan*/  UCS4_ESC ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * xdig ; 

__attribute__((used)) static __inline int
to_str(char *s, wchar_t wc, int bit)
{
	char *p;

	p = s;
	*p++ = ESCAPE;
	switch (bit) {
	case UCS2_BIT:
		*p++ = UCS2_ESC;
		break;
	case UCS4_BIT:
		*p++ = UCS4_ESC;
		break;
	default:
		abort();
	}
	do {
		*p++ = xdig[(wc >> (bit -= 4)) & 0xF];
	} while (bit > 0);
	return (p - s);
}