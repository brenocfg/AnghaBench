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
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  errno ; 
 int iconv_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
close_1(void)
{
	iconv_t cd = (iconv_t)-1;

	return ((iconv_close(cd) == -1) && (errno = EBADF) ? 0 : 1);
}