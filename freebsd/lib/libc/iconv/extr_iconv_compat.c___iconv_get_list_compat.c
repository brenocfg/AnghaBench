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
typedef  int /*<<< orphan*/  __iconv_bool ;

/* Variables and functions */
 int __bsd___iconv_get_list (char***,size_t*,int /*<<< orphan*/ ) ; 

int
__iconv_get_list_compat(char ***a, size_t *b, __iconv_bool c)
{
	return __bsd___iconv_get_list(a, b, c);
}