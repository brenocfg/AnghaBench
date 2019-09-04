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
struct TYPE_5__ {char* attributes; int /*<<< orphan*/  stream; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ git_filter ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_VERSION ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  compress_filter_stream_init ; 
 TYPE_1__* git__calloc (int,int) ; 

git_filter *create_compress_filter(void)
{
	git_filter *filter = git__calloc(1, sizeof(git_filter));
	cl_assert(filter);

	filter->version = GIT_FILTER_VERSION;
	filter->attributes = "+compress";
	filter->stream = compress_filter_stream_init;

	return filter;
}