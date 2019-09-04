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
struct TYPE_3__ {char const* content; size_t content_len; size_t content_offset; } ;
typedef  TYPE_1__ git_diff_line ;

/* Variables and functions */

__attribute__((used)) static void patch_line_init(
	git_diff_line *out,
	const char *in,
	size_t in_len,
	size_t in_offset)
{
	out->content = in;
	out->content_len = in_len;
	out->content_offset = in_offset;
}