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
typedef  int /*<<< orphan*/  iconv_t ;
typedef  int /*<<< orphan*/  __uint32_t ;

/* Variables and functions */
 size_t __bsd___iconv (int /*<<< orphan*/ ,char**,size_t*,char**,size_t*,int /*<<< orphan*/ ,size_t*) ; 

size_t
__iconv(iconv_t a, char **b, size_t *c, char **d,
     size_t *e, __uint32_t f, size_t *g)
{
	return __bsd___iconv(a, b, c, d, e, f, g);
}