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
 scalar_t__ istarts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 

__attribute__((used)) static int same_utf_encoding(const char *src, const char *dst)
{
	if (istarts_with(src, "utf") && istarts_with(dst, "utf")) {
		/* src[3] or dst[3] might be '\0' */
		int i = (src[3] == '-' ? 4 : 3);
		int j = (dst[3] == '-' ? 4 : 3);
		return !strcasecmp(src+i, dst+j);
	}
	return 0;
}