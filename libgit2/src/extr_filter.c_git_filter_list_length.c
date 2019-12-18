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
struct TYPE_3__ {int /*<<< orphan*/  filters; } ;
typedef  TYPE_1__ git_filter_list ;

/* Variables and functions */
 size_t git_array_size (int /*<<< orphan*/ ) ; 

size_t git_filter_list_length(const git_filter_list *fl)
{
	return fl ? git_array_size(fl->filters) : 0;
}