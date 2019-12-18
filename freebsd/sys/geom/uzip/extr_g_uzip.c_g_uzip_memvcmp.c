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
typedef  unsigned char u_char ;

/* Variables and functions */
 scalar_t__ memcmp (unsigned char const*,unsigned char const*,size_t) ; 

__attribute__((used)) static int
g_uzip_memvcmp(const void *memory, unsigned char val, size_t size)
{
	const u_char *mm;

	mm = (const u_char *)memory;
	return (*mm == val) && memcmp(mm, mm + 1, size - 1) == 0;
}