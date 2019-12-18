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
 void __bsd_iconv_set_relocation_prefix (char const*,char const*) ; 

void
iconv_set_relocation_prefix_compat(const char *a, const char *b)
{
	return __bsd_iconv_set_relocation_prefix(a, b);
}