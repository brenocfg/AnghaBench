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
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  ICONV_SET_TRANSLITERATE ; 
 int iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char*,char*) ; 
 scalar_t__ iconvctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
ctl_set_translit1(void)
{
	iconv_t cd;
	int arg = 1, ret;

	cd = iconv_open("ASCII", "UTF-8");
	if (cd == (iconv_t)-1)
		return (-1);
	ret = iconvctl(cd, ICONV_SET_TRANSLITERATE, &arg) == 0 ? 0 : -1;
	if (iconv_close(cd) == -1)
		return (-1);
	return (ret);
}