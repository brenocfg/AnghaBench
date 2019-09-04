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
 int git_config_bool (char const*,char const*) ; 

__attribute__((used)) static int parse_bool(int *b, const char *k, const char *v)
{
	*b = git_config_bool(k, v);
	return 0;
}