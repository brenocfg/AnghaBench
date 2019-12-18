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
 scalar_t__ EINVAL ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char*,char*) ; 

__attribute__((used)) static int
open_1(void)
{
	iconv_t cd;

	errno = 0;
	cd = iconv_open("nonexisting", "foobar");

	if ((cd == (iconv_t)-1) && (errno == EINVAL))
		return (0);
	else {
		iconv_close(cd);
		return (1);
	}
}