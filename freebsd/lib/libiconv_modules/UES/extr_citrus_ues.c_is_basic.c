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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static __inline bool
is_basic(wchar_t wc)
{

	return ((uint32_t)wc <= 0x9F && wc != 0x24 && wc != 0x40 &&
	    wc != 0x60);
}