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

__attribute__((used)) static size_t
html_replace(const char ch, const char **escaped)
{
	switch (ch) {
	case '<':
		*escaped = "&lt;";
		return 4;
	case '>':
		*escaped = "&gt;";
		return 4;
	case '"':
		*escaped = "&quot;";
		return 6;
	case '\'':
		*escaped = "&#039;";
		return 6;
	case '&':
		*escaped = "&amp;";
		return 5;
	default:
		break;
	}

	return 1;
}