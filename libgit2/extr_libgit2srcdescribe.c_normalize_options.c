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
struct TYPE_5__ {scalar_t__ max_candidates_tags; } ;
typedef  TYPE_1__ git_describe_options ;

/* Variables and functions */
 scalar_t__ GIT_DESCRIBE_DEFAULT_MAX_CANDIDATES_TAGS ; 
 TYPE_1__ GIT_DESCRIBE_OPTIONS_INIT ; 

__attribute__((used)) static int normalize_options(
	git_describe_options *dst,
	const git_describe_options *src)
{
	git_describe_options default_options = GIT_DESCRIBE_OPTIONS_INIT;
	if (!src) src = &default_options;

	*dst = *src;

	if (dst->max_candidates_tags > GIT_DESCRIBE_DEFAULT_MAX_CANDIDATES_TAGS)
		dst->max_candidates_tags = GIT_DESCRIBE_DEFAULT_MAX_CANDIDATES_TAGS;

	return 0;
}