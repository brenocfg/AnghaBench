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
typedef  int wchar_t ;

/* Variables and functions */
 int wcwidth (int const) ; 

__attribute__((used)) static int
width(const wchar_t *wcs)
{
	int w, cw;

	for (w = 0; *wcs != L'\0'; wcs++)
		if ((cw = wcwidth(*wcs)) > 0)
			w += cw;
	return (w);
}