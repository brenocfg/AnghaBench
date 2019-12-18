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
typedef  scalar_t__ wchar_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static __inline int
_mb_count(wchar_t v)
{
	uint32_t c;

	c = (uint32_t)v; /* XXX */
	if (!(c & 0xffffff00))
		return (1);
	if (!(c & 0xffff0000))
		return (2);
	return (4);
}