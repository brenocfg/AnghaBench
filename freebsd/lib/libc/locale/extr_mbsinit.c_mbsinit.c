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
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  __get_locale () ; 
 int mbsinit_l (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int
mbsinit(const mbstate_t *ps)
{
	return mbsinit_l(ps, __get_locale());
}