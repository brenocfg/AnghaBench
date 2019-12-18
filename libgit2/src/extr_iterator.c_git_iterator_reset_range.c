#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* cb; } ;
typedef  TYPE_2__ git_iterator ;
struct TYPE_6__ {int (* reset ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ iterator_reset_range (TYPE_2__*,char const*,char const*) ; 
 int stub1 (TYPE_2__*) ; 

int git_iterator_reset_range(
	git_iterator *i, const char *start, const char *end)
{
	if (iterator_reset_range(i, start, end) < 0)
		return -1;

	return i->cb->reset(i);
}