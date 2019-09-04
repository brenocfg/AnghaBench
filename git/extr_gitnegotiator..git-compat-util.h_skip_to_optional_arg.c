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
 int skip_to_optional_arg_default (char const*,char const*,char const**,char*) ; 

__attribute__((used)) static inline int skip_to_optional_arg(const char *str, const char *prefix,
				       const char **arg)
{
	return skip_to_optional_arg_default(str, prefix, arg, "");
}