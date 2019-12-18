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

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kstrdup_const (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_cpy_name(const char **dst_p, const char *src, bool must_exist)
{
	const char *dst;

	if (!src) {
		if (must_exist)
			return -EINVAL;
		return 0;
	}

	*dst_p = dst = kstrdup_const(src, GFP_KERNEL);
	if (!dst)
		return -ENOMEM;

	return 0;
}