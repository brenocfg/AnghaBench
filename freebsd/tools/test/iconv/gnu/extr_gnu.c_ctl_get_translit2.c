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
 int /*<<< orphan*/  ICONV_GET_TRANSLITERATE ; 
 int iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char*,char*) ; 
 scalar_t__ iconvctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
ctl_get_translit2(void)
{
	iconv_t cd;
	int arg, ret;

	cd = iconv_open("ASCII", "UTF-8");
	if (cd == (iconv_t)-1)
		return (-1);
	if (iconvctl(cd, ICONV_GET_TRANSLITERATE, &arg) == 0)
		ret = (arg == 0) ? 0 : -1;
	else
		ret = -1;
	if (iconv_close(cd) == -1)
		return (-1);
	return (ret);
}