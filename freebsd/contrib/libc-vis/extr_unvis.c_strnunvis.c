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
 int strnunvisx (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

int
strnunvis(char *dst, size_t dlen, const char *src)
{
	return strnunvisx(dst, dlen, src, 0);
}