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

/* Variables and functions */
 size_t __bsd_iconv (int /*<<< orphan*/ ,char**,size_t*,char**,size_t*) ; 

size_t
iconv_compat(iconv_t a, char ** __restrict b,
      size_t * __restrict c, char ** __restrict d,
      size_t * __restrict e)
{
	return __bsd_iconv(a, b, c, d, e);
}