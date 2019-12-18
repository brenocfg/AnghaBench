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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int /*<<< orphan*/  wc; } ;
typedef  TYPE_1__ charmap_t ;

/* Variables and functions */
 scalar_t__ RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cmap_wc ; 

int
check_charmap(wchar_t wc)
{
	charmap_t srch;

	srch.wc = wc;
	return (RB_FIND(cmap_wc, &cmap_wc, &srch) ? 0 : -1);
}