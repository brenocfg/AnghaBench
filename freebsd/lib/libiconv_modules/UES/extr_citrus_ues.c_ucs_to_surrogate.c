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

__attribute__((used)) static __inline void
ucs_to_surrogate(wchar_t wc, wchar_t * __restrict hi, wchar_t * __restrict lo)
{

	wc -= 0x10000;
	*hi = (wc >> 10) + 0xD800;
	*lo = (wc & 0x3FF) + 0xDC00;
}