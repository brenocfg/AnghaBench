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
typedef  int /*<<< orphan*/  git_describe_format_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DESCRIBE_FORMAT_OPTIONS_VERSION ; 
 int /*<<< orphan*/  git_describe_format_options_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int normalize_format_options(
	git_describe_format_options *dst,
	const git_describe_format_options *src)
{
	if (!src) {
		git_describe_format_options_init(dst, GIT_DESCRIBE_FORMAT_OPTIONS_VERSION);
		return 0;
	}

	memcpy(dst, src, sizeof(git_describe_format_options));
	return 0;
}