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

/* Variables and functions */
 int /*<<< orphan*/  isxdigit (char const) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int
StrHexToBytes(const char *str, size_t len, uint8_t *buf, size_t buflen)
{
	size_t i;
	char hex[3];

	/*
	 * Sanity check preconditions.
	 */
	if (buflen != len / 2 || (len % 2) == 1)
		return 1;
	for (i = 0; i < len; i += 2) {
		if (!isxdigit(str[i]) || !isxdigit(str[i + 1]))
			return 1;
		hex[0] = str[i];
		hex[1] = str[i + 1];
		hex[2] = '\0';
		buf[i / 2] = strtol(hex, NULL, 16);
	}
	return 0;
}