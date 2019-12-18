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
 int /*<<< orphan*/  isascii (int) ; 

__attribute__((used)) static int has_only_ascii(const char *s)
{
	for (;;) {
		int c = *s++;
		if (c == '\0')
			return 1;
		if (!isascii(c))
			return 0;
	}
}