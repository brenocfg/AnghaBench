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
 int /*<<< orphan*/  __bsd___iconv_open (char const*,char const*,int /*<<< orphan*/ *) ; 

iconv_t
__bsd_iconv_open(const char *out, const char *in)
{

	return (__bsd___iconv_open(out, in, NULL));
}