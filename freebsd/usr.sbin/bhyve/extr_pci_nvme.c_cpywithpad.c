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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 size_t strnlen (char const*,size_t) ; 

__attribute__((used)) static __inline void
cpywithpad(char *dst, size_t dst_size, const char *src, char pad)
{
	size_t len;

	len = strnlen(src, dst_size);
	memset(dst, pad, dst_size);
	memcpy(dst, src, len);
}