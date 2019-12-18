#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int word_type ;
struct TYPE_3__ {scalar_t__ low; scalar_t__ high; } ;
struct TYPE_4__ {unsigned long long ll; TYPE_1__ s; } ;
typedef  TYPE_2__ DWunion ;

/* Variables and functions */

word_type __ucmpdi2(unsigned long long a, unsigned long long b)
{
	const DWunion au = {.ll = a};
	const DWunion bu = {.ll = b};

	if ((unsigned int) au.s.high < (unsigned int) bu.s.high)
		return 0;
	else if ((unsigned int) au.s.high > (unsigned int) bu.s.high)
		return 2;
	if ((unsigned int) au.s.low < (unsigned int) bu.s.low)
		return 0;
	else if ((unsigned int) au.s.low > (unsigned int) bu.s.low)
		return 2;
	return 1;
}