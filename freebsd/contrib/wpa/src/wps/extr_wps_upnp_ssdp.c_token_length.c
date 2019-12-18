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
 scalar_t__ isalnum (int) ; 

__attribute__((used)) static int token_length(const char *s)
{
	const char *begin = s;
	for (;; s++) {
		int c = *s;
		int end = !(isalnum(c) || c == '_' || c == '-');
		if (end)
			break;
	}
	return s - begin;
}