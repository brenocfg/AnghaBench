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
 int /*<<< orphan*/  utf8_width (char const**,int /*<<< orphan*/ *) ; 

int is_utf8(const char *text)
{
	while (*text) {
		if (*text == '\n' || *text == '\t' || *text == '\r') {
			text++;
			continue;
		}
		utf8_width(&text, NULL);
		if (!text)
			return 0;
	}
	return 1;
}