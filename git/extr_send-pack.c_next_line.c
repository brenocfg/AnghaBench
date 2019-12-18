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
 char* memchr (char const*,char,size_t) ; 

__attribute__((used)) static const char *next_line(const char *line, size_t len)
{
	const char *nl = memchr(line, '\n', len);
	if (!nl)
		return line + len; /* incomplete line */
	return nl + 1;
}