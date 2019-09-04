#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* attributes; int /*<<< orphan*/  apply; int /*<<< orphan*/  shutdown; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ git_filter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_VERSION ; 
 int /*<<< orphan*/  bitflip_filter_apply ; 
 int /*<<< orphan*/  bitflip_filter_free ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 

git_filter *create_bitflip_filter(void)
{
	git_filter *filter = git__calloc(1, sizeof(git_filter));
	cl_assert(filter);

	filter->version = GIT_FILTER_VERSION;
	filter->attributes = "+bitflip";
	filter->shutdown = bitflip_filter_free;
	filter->apply = bitflip_filter_apply;

	return filter;
}