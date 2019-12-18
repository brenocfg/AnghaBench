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
 unsigned int hexval (char const) ; 

__attribute__((used)) static inline int hex2chr(const char *s)
{
	unsigned int val = hexval(s[0]);
	return (val & ~0xf) ? val : (val << 4) | hexval(s[1]);
}