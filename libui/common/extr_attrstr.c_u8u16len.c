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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ uiprivUTF16EncodeRune (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* uiprivUTF8DecodeRune (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ uiprivUTF8EncodeRune (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void u8u16len(const char *str, size_t *n8, size_t *n16)
{
	uint32_t rune;
	char buf[4];
	uint16_t buf16[2];

	*n8 = 0;
	*n16 = 0;
	while (*str) {
		str = uiprivUTF8DecodeRune(str, 0, &rune);
		// TODO document the use of the function vs a pointer subtract here
		// TODO also we need to consider namespace collision with utf.h...
		*n8 += uiprivUTF8EncodeRune(rune, buf);
		*n16 += uiprivUTF16EncodeRune(rune, buf16);
	}
}