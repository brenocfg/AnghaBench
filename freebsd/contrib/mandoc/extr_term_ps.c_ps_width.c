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
struct termp {int dummy; } ;
struct TYPE_4__ {TYPE_1__* gly; } ;
struct TYPE_3__ {int /*<<< orphan*/  wx; } ;

/* Variables and functions */
 int MAXCHAR ; 
 scalar_t__ TERMFONT_NONE ; 
 TYPE_2__* fonts ; 

__attribute__((used)) static size_t
ps_width(const struct termp *p, int c)
{

	if (c <= 32 || c - 32 >= MAXCHAR)
		c = 0;
	else
		c -= 32;

	return (size_t)fonts[(int)TERMFONT_NONE].gly[c].wx;
}