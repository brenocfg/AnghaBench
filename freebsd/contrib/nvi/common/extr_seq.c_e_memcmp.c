#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ e_c; } ;
typedef  TYPE_1__ EVENT ;
typedef  int CHAR_T ;

/* Variables and functions */

int
e_memcmp(
	CHAR_T *p1,
	EVENT *ep,
	size_t n)
{
	if (n != 0) {
		do {
			if (*p1++ != ep->e_c)
				return (*--p1 - ep->e_c);
			++ep;
		} while (--n != 0);
	}
	return (0);
}