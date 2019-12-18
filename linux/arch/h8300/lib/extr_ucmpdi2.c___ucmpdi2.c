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
typedef  scalar_t__ UWtype ;
struct TYPE_3__ {scalar_t__ low; scalar_t__ high; } ;
struct TYPE_4__ {TYPE_1__ s; int /*<<< orphan*/  ll; } ;
typedef  TYPE_2__ DWunion ;
typedef  int /*<<< orphan*/  DWtype ;

/* Variables and functions */

word_type __ucmpdi2(DWtype a, DWtype b)
{
	const DWunion au = {.ll = a};
	const DWunion bu = {.ll = b};

	if ((UWtype) au.s.high < (UWtype) bu.s.high)
		return 0;
	else if ((UWtype) au.s.high > (UWtype) bu.s.high)
		return 2;
	if ((UWtype) au.s.low < (UWtype) bu.s.low)
		return 0;
	else if ((UWtype) au.s.low > (UWtype) bu.s.low)
		return 2;
	return 1;
}